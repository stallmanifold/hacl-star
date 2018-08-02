#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "kremlib.h"
#include "Crypto_HKDF_Crypto_HMAC.h"
#include "EverCrypt.h"
#include "quic_provider.h"

#define DEBUG 0

typedef struct quic_key {
  mitls_aead alg;
  unsigned char key[32];
  unsigned char static_iv[12];
  union {
    unsigned char case_chacha20[32];
    EverCrypt_aes128_key case_aes128;
    EverCrypt_aes256_key case_aes256;
  } pne;
} quic_key;

#if DEBUG
static void dump(const unsigned char buffer[], size_t len)
{
  size_t i;
  for(i=0; i<len; i++) {
    printf("%02x",buffer[i]);
    if (i % 32 == 31 || i == len-1) printf("\n");
  }
}

static void dump_secret(const quic_secret *s)
{
  const char *ha =
    s->hash == TLS_hash_SHA256 ? "SHA256" :
    (s->hash == TLS_hash_SHA384 ? "SHA384" :
      (s->hash == TLS_hash_SHA512 ? "SHA512" : "BAD"));
  const char *ae =
    s->ae == TLS_aead_AES_128_GCM ? "AES-128-GCM" :
      (s->ae == TLS_aead_CHACHA20_POLY1305 ? "CHACHA20-POLY1305" :
        (s->ae == TLS_aead_AES_256_GCM ? "AES-256-GCM" : "BAD"));
  printf("SECRET %s %s\n", ha, ae);
  uint32_t hlen = (s->hash == TLS_hash_SHA256 ? 32 :
    (s->hash == TLS_hash_SHA384 ? 48 : 64));
  dump(s->secret, hlen);
}
#endif

#define CONVERT_ALG(a) \
  (a == TLS_hash_SHA256 ? Crypto_HMAC_SHA256 : \
    (a == TLS_hash_SHA384 ? Crypto_HMAC_SHA384 : Crypto_HMAC_SHA512))

int MITLS_CALLCONV quic_crypto_hash(quic_hash a, /*out*/ unsigned char *hash, const unsigned char *data, size_t len){
  if(a < TLS_hash_SHA256) return 0;
  Crypto_HMAC_agile_hash(CONVERT_ALG(a), (uint8_t*) hash, (uint8_t*)data, len);
  return 1;
}

int MITLS_CALLCONV quic_crypto_hmac(quic_hash a, unsigned char *mac,
                     const unsigned char *key, uint32_t key_len,
                     const unsigned char *data, uint32_t data_len) {
  if(a < TLS_hash_SHA256) return 0;
  Crypto_HMAC_hmac(CONVERT_ALG(a), (uint8_t*) mac, (uint8_t*)key, key_len, (uint8_t*)data, data_len);
  return 1;
}

int MITLS_CALLCONV quic_crypto_hkdf_extract(quic_hash a, unsigned char *prk,
                             const unsigned char *salt, uint32_t salt_len,
                             const unsigned char *ikm, uint32_t ikm_len)
{
  if(a < TLS_hash_SHA256) return 0;
  Crypto_HKDF_hkdf_extract(CONVERT_ALG(a), (uint8_t*) prk, (uint8_t*)salt, salt_len, (uint8_t*)ikm, ikm_len);
  return 1;
}

int MITLS_CALLCONV quic_crypto_hkdf_expand(quic_hash a, unsigned char *okm, uint32_t olen, const unsigned char *prk, uint32_t prk_len, const unsigned char *info, uint32_t info_len)
{
  if(a < TLS_hash_SHA256) return 0;
  Crypto_HKDF_hkdf_expand(CONVERT_ALG(a), (uint8_t*) okm, (uint8_t*)prk, prk_len, (uint8_t*)info, info_len, olen);
  return 1;
}

int MITLS_CALLCONV quic_crypto_hkdf_tls_label(quic_hash a, unsigned char *info, size_t *info_len, const char *label)
{
  size_t label_len = strlen(label);
  uint32_t hlen = (a == TLS_hash_SHA256 ? 32 : (a == TLS_hash_SHA384 ? 48 : 64));
  unsigned char *hash = alloca(hlen);

  if(a < TLS_hash_SHA256 || !info || !hash || label_len > 249)
    return 0;

  info[0] = 0;
  info[1] = hlen;
  info[2] = label_len + 6;
  memcpy(info+3, "tls13 ", 6);
  memcpy(info+9, label, label_len);

  if(!quic_crypto_hash(a, hash, (const unsigned char*)label, 0))
    return 0;

  info[9+label_len] = hlen;
  memcpy(info + label_len + 10, hash, hlen);
  *info_len = label_len + 10 + hlen;

  return 1;
}

int MITLS_CALLCONV quic_crypto_hkdf_quic_label(quic_hash a, unsigned char *info, size_t *info_len, const char *label, uint16_t key_len)
{
  uint32_t hlen = (a == TLS_hash_SHA256 ? 32 :
    (a == TLS_hash_SHA384 ? 48 : 64));
  size_t label_len = strlen(label);

  if(a < TLS_hash_SHA256 || !info || label_len > 249)
    return 0;

  info[0] = key_len >> 8;
  info[1] = key_len & 255;
  info[2] = (char)(label_len + 5);
  memcpy(info+3, "QUIC ", 5);
  memcpy(info+8, label, label_len);
  *info_len = label_len + 8;

  return 1;
}

int MITLS_CALLCONV quic_crypto_tls_derive_secret(quic_secret *derived, const quic_secret *secret, const char *label)
{
  uint32_t hlen = (secret->hash == TLS_hash_SHA256 ? 32 :
    (secret->hash == TLS_hash_SHA384 ? 48 : 64));
  unsigned char *tmp = alloca(hlen);
  unsigned char info[323] = {0};
  size_t info_len;

  if(!quic_crypto_hkdf_tls_label(secret->hash, info, &info_len, label))
    return 0;

  derived->hash = secret->hash;
  derived->ae = secret->ae;

#if DEBUG
  printf("Secret to expand <%s>:\n", label);
  dump_secret(secret);
#endif

  if(!quic_crypto_hkdf_expand(secret->hash, tmp, hlen,
        (uint8_t*) secret->secret, hlen, info, info_len))
    return 0;

#if DEBUG
  printf("Intermediate:\n");
  dump(tmp, hlen);
#endif

  if(!quic_crypto_hkdf_tls_label(secret->hash, info, &info_len, "exporter"))
    return 0;

  if(!quic_crypto_hkdf_expand(secret->hash, (uint8_t *) derived->secret, hlen,
        tmp, hlen, info, info_len))
    return 0;

#if DEBUG
  printf("Derived:\n");
  dump_secret(derived);
#endif

  return 1;
}

int MITLS_CALLCONV quic_derive_initial_secrets(quic_secret *client_in, quic_secret *server_in,
   const unsigned char *con_id, size_t con_id_len, const unsigned char *salt, size_t salt_len, uint8_t is_draft13)
{
  quic_secret s0 = {
    .hash = TLS_hash_SHA256,
    .ae = TLS_aead_AES_128_GCM,
    .secret = {0}
  };
  unsigned char info[259] = {0};
  size_t info_len;

  #if DEBUG
    printf("ConnID:\n");
    dump(con_id, con_id_len);
    printf("Salt:\n");
    dump(salt, salt_len);
  #endif

  if(!quic_crypto_hkdf_extract(s0.hash, (uint8_t *) s0.secret, salt, salt_len, con_id, con_id_len))
    return 0;

#if DEBUG
  printf("Extracted CID:\n");
  dump(s0.secret, 32);
#endif

  client_in->hash = s0.hash;
  client_in->ae = s0.ae;

  if(!quic_crypto_hkdf_quic_label(s0.hash, info, &info_len, is_draft13 ? "client in" : "client hs", 32))
    return 0;

  if(!quic_crypto_hkdf_expand(s0.hash, (uint8_t *) client_in->secret, 32, (uint8_t *) s0.secret, 32, info, info_len))
    return 0;

  #if DEBUG
    printf("Client HS:\n");
    dump(client_in->secret, 32);
  #endif

  server_in->hash = s0.hash;
  server_in->ae = s0.ae;

  if(!quic_crypto_hkdf_quic_label(s0.hash, info, &info_len, is_draft13 ? "server in" : "server hs", 32))
    return 0;

  if(!quic_crypto_hkdf_expand(s0.hash, (uint8_t *) server_in->secret, 32, (uint8_t *) s0.secret, 32, info, info_len))
    return 0;

  #if DEBUG
    printf("Server HS:\n");
    dump(server_in->secret, 32);
  #endif

  return 1;
}

int MITLS_CALLCONV quic_crypto_derive_key(quic_key **k, const quic_secret *secret)
{
  quic_key *key = KRML_HOST_MALLOC(sizeof(quic_key));
  if(!key) return 0;
  key->alg = secret->ae;

  uint32_t klen = (secret->ae == TLS_aead_AES_128_GCM ? 16 : 32);
  uint32_t slen = (secret->hash == TLS_hash_SHA256 ? 32 : (secret->hash == TLS_hash_SHA384 ? 48 : 64));

  unsigned char info[259] = {0};
  unsigned char pnkey[32];
  size_t info_len;

  if(!quic_crypto_hkdf_quic_label(secret->hash, info, &info_len, "key", klen))
    return 0;
  if(!quic_crypto_hkdf_expand(secret->hash, key->key, klen, (uint8_t *) secret->secret, slen, info, info_len))
    return 0;

  if(!quic_crypto_hkdf_quic_label(secret->hash, info, &info_len, "iv", 12))
    return 0;
  if(!quic_crypto_hkdf_expand(secret->hash, key->static_iv, 12, (uint8_t *) secret->secret, slen, info, info_len))
    return 0;

  if(!quic_crypto_hkdf_quic_label(secret->hash, info, &info_len, "pn", klen))
    return 0;
  if(!quic_crypto_hkdf_expand(secret->hash, pnkey, klen, (uint8_t *) secret->secret, slen, info, info_len))
    return 0;

#if DEBUG
   printf("KEY: "); dump(dkey, klen);
   printf("IV: "); dump(key->static_iv, 12);
   printf("PNE: "); dump(pnkey, klen);
#endif

   if(key->alg == TLS_aead_AES_128_GCM)
   {
     key->pne.case_aes128 = EverCrypt_aes128_create(pnkey);
   }
   else if(key->alg == TLS_aead_AES_256_GCM)
   {
     key->pne.case_aes256 = EverCrypt_aes256_create(pnkey);
   }
   else if(key->alg == TLS_aead_CHACHA20_POLY1305)
   {
     memcpy(key->pne.case_chacha20, pnkey, 32);
   }

  *k = key;
  return 1;
}

static inline void sn_to_iv(unsigned char *iv, uint64_t sn)
{
  for(int i = 4; i < 12; i++)
    iv[i] ^= (sn >> (88-(i<<3))) & 255;
}

int MITLS_CALLCONV quic_crypto_create(quic_key **key, mitls_aead alg, const unsigned char *raw_key, const unsigned char *iv, const unsigned char *pne_key)
{
  quic_key *k = KRML_HOST_MALLOC(sizeof(quic_key));
  if(!k) return 0;
  uint32_t klen = (alg == TLS_aead_AES_128_GCM ? 16 : 32);

  k->alg = alg;
  memcpy(k->key, raw_key, klen);
  memcpy(k->static_iv, iv, 12);

  if(alg == TLS_aead_AES_128_GCM)
    k->pne.case_aes128 = EverCrypt_aes128_create(pne_key);
  else if(alg == TLS_aead_AES_256_GCM)
    k->pne.case_aes256 = EverCrypt_aes256_create(pne_key);
  else if(alg == TLS_aead_CHACHA20_POLY1305)
    memcpy(k->pne.case_chacha20, pne_key, 32);

  *key = k;
  return 1;
}

int MITLS_CALLCONV quic_crypto_encrypt(quic_key *key, unsigned char *cipher, uint64_t sn,
  const unsigned char *ad, uint32_t ad_len, const unsigned char *plain, uint32_t plain_len)
{
  unsigned char iv[12];
  memcpy(iv, key->static_iv, 12);
  sn_to_iv(iv, sn);

  if(key->alg == TLS_aead_AES_128_GCM)
  {
    EverCrypt_aes128_gcm_encrypt(key->key, iv, ad, ad_len, plain, plain_len, cipher, (cipher+plain_len));
  }
  else if(key->alg == TLS_aead_AES_256_GCM)
  {
    EverCrypt_aes256_gcm_encrypt(key->key, iv, ad, ad_len, plain, plain_len, cipher, (cipher+plain_len));
  }
  else if(key->alg == TLS_aead_CHACHA20_POLY1305)
  {
    EverCrypt_chacha20_poly1305_encrypt(key->key, iv, ad, ad_len, plain, plain_len, cipher, (cipher+plain_len));
  }

#if DEBUG
  printf("ENCRYPT\nIV="); dump(iv, 12);
  printf("STATIC="); dump(key->static_iv, 12);
  printf("AD="); dump(ad, ad_len);
  printf("PLAIN="); dump(plain, plain_len);
  printf("CIPHER="); dump(cipher, plain_len + 16);
#endif

  return 1;
}

int MITLS_CALLCONV quic_crypto_decrypt(quic_key *key, unsigned char *plain, uint64_t sn,
  const unsigned char *ad, uint32_t ad_len, const unsigned char *cipher, uint32_t cipher_len)
{
  unsigned char iv[12];
  memcpy(iv, key->static_iv, 12);
  sn_to_iv(iv, sn);

  if(cipher_len < quic_crypto_tag_length(key))
    return 0;

  uint32_t r, plain_len = cipher_len - quic_crypto_tag_length(key);

  if(key->alg == TLS_aead_AES_128_GCM)
  {
    r = EverCrypt_aes128_gcm_decrypt(key->key, iv, ad, ad_len, plain, plain_len, cipher, (cipher+plain_len));
  }
  else if(key->alg == TLS_aead_AES_256_GCM)
  {
    r = EverCrypt_aes256_gcm_decrypt(key->key, iv, ad, ad_len, plain, plain_len, cipher, (cipher+plain_len));
  }
  else if(key->alg == TLS_aead_CHACHA20_POLY1305)
  {
    r = EverCrypt_chacha20_poly1305_decrypt(key->key, iv, ad, ad_len, plain, plain_len, cipher, (cipher+plain_len));
  }

#if DEBUG
  printf("DECRYPT %s\nIV=", r?"OK":"BAD"); dump(iv, 12);
  printf("STATIC="); dump(key->static_iv, 12);
  printf("AD="); dump(ad, ad_len);
  printf("CIPHER="); dump(cipher, cipher_len);
  printf("PLAIN="); dump(plain, plain_len);
#endif

  return r;
}

int MITLS_CALLCONV quic_crypto_packet_number_otp(quic_key *key, const unsigned char *sample, unsigned char *mask)
{
  unsigned char block[16];
  if(key->alg == TLS_aead_AES_128_GCM)
  {
    EverCrypt_aes128_compute(key->pne.case_aes128, sample, block);
    memcpy(mask, block, 4);
    return 1;
  }

  if(key->alg == TLS_aead_AES_256_GCM)
  {
    EverCrypt_aes256_compute(key->pne.case_aes256, sample, block);
    memcpy(mask, block, 4);
    return 1;
  }

  if(key->alg == TLS_aead_CHACHA20_POLY1305)
  {
    uint8_t zero[4] = {0};
    uint32_t ctr = sample[0] + (sample[1] << 8) + (sample[2] << 16) + (sample[3] << 24);

    EverCrypt_chacha20((uint8_t*)key->pne.case_chacha20, sample+4, ctr, zero, 4, mask);
    return 1;
  }

  return 0;
}

int MITLS_CALLCONV quic_crypto_free_key(quic_key *key)
{
  if(key != NULL)
  {
    if(key->alg == TLS_aead_AES_128_GCM)
      EverCrypt_aes128_free(key->pne.case_aes128);
    if(key->alg == TLS_aead_AES_256_GCM)
      EverCrypt_aes256_free(key->pne.case_aes256);
    KRML_HOST_FREE(key);
  }
  return 1;
}