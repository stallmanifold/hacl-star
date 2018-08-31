/* This file was generated by KreMLin <https://github.com/FStarLang/kremlin>
 * KreMLin invocation: /home/rpk/kremlin/krml -I /home/rpk/kremlin/kremlib/compat -I /mnt/c/hacl-star/code/lib/kremlin -I /home/rpk/kremlin/kremlib/compat -I /mnt/c/hacl-star/specs -I . -ccopt -march=native -verbose -ldopt -flto -tmpdir mpfr-c mpfr-c/out.krml -skip-compilation -minimal -add-include "kremlib.h" -bundle MPFR=* -fparentheses
 * F* version: 3352fef9
 * KreMLin version: c65d4779
 */

#include "MPFR.h"

extern FStar_UInt128_uint128 FStar_UInt128_shift_right(FStar_UInt128_uint128 x0, uint32_t x1);

extern uint64_t FStar_UInt128_uint128_to_uint64(FStar_UInt128_uint128 x0);

extern FStar_UInt128_uint128 FStar_UInt128_mul_wide(uint64_t x0, uint64_t x1);

static bool MPFR_RoundingMode_uu___is_MPFR_RNDN(MPFR_RoundingMode_mpfr_rnd_t projectee)
{
  switch (projectee)
  {
    case MPFR_RoundingMode_MPFR_RNDN:
      {
        return true;
      }
    default:
      {
        return false;
      }
  }
}

static bool MPFR_RoundingMode_uu___is_MPFR_RNDZ(MPFR_RoundingMode_mpfr_rnd_t projectee)
{
  switch (projectee)
  {
    case MPFR_RoundingMode_MPFR_RNDZ:
      {
        return true;
      }
    default:
      {
        return false;
      }
  }
}

static bool MPFR_RoundingMode_uu___is_MPFR_RNDU(MPFR_RoundingMode_mpfr_rnd_t projectee)
{
  switch (projectee)
  {
    case MPFR_RoundingMode_MPFR_RNDU:
      {
        return true;
      }
    default:
      {
        return false;
      }
  }
}

static bool MPFR_RoundingMode_uu___is_MPFR_RNDD(MPFR_RoundingMode_mpfr_rnd_t projectee)
{
  switch (projectee)
  {
    case MPFR_RoundingMode_MPFR_RNDD:
      {
        return true;
      }
    default:
      {
        return false;
      }
  }
}

static bool MPFR_RoundingMode_uu___is_MPFR_RNDA(MPFR_RoundingMode_mpfr_rnd_t projectee)
{
  switch (projectee)
  {
    case MPFR_RoundingMode_MPFR_RNDA:
      {
        return true;
      }
    default:
      {
        return false;
      }
  }
}

static bool MPFR_RoundingMode_mpfr_IS_LIKE_RNDZ(MPFR_RoundingMode_mpfr_rnd_t rnd, bool neg)
{
  return
    MPFR_RoundingMode_uu___is_MPFR_RNDZ(rnd)
    || (MPFR_RoundingMode_uu___is_MPFR_RNDU(rnd) && neg)
    || (MPFR_RoundingMode_uu___is_MPFR_RNDD(rnd) && !neg);
}

static bool MPFR_RoundingMode_mpfr_IS_LIKE_RNDA(MPFR_RoundingMode_mpfr_rnd_t rnd, bool neg)
{
  return
    MPFR_RoundingMode_uu___is_MPFR_RNDA(rnd)
    || (MPFR_RoundingMode_uu___is_MPFR_RNDD(rnd) && neg)
    || (MPFR_RoundingMode_uu___is_MPFR_RNDD(rnd) && !neg);
}

static int64_t MPFR_Lib_gmp_NUMB_BITS = (int64_t)64;

static int64_t MPFR_Lib_mpfr_EXP_ZERO = (int64_t)-0x7fffffffffffffff;

static int64_t MPFR_Lib_mpfr_EXP_INF = (int64_t)-0x7ffffffffffffffd;

static int64_t MPFR_Lib_mpfr_EMIN = (int64_t)-0x3fffffffffffffff;

static int64_t MPFR_Lib_mpfr_EMAX = (int64_t)0x3fffffffffffffff;

static void MPFR_Lib_mpfr_SET_EXP(MPFR_Lib_mpfr_struct *x, int64_t e)
{
  MPFR_Lib_mpfr_struct uu___54_3394 = x[0U];
  x[0U] =
    (
      (MPFR_Lib_mpfr_struct){
        .mpfr_prec = uu___54_3394.mpfr_prec,
        .mpfr_sign = uu___54_3394.mpfr_sign,
        .mpfr_exp = e,
        .mpfr_d = uu___54_3394.mpfr_d
      }
    );
}

static int32_t MPFR_Lib_mpfr_NEG_SIGN(int32_t s)
{
  if (s == (int32_t)1)
    return (int32_t)-1;
  else
    return (int32_t)1;
}

static void MPFR_Lib_mpn_ZERO(uint64_t *b, int64_t l)
{
  if (!(l == (int64_t)0))
  {
    b[(uint32_t)(l - (int64_t)1)] = (uint64_t)0U;
    MPFR_Lib_mpn_ZERO(b, l - (int64_t)1);
  }
}

static int32_t MPFR_Lib_mpfr_RET(int32_t t)
{
  return t;
}

static void MPFR_Lib_mpfr_setmax_rec(MPFR_Lib_mpfr_struct *x, int64_t i)
{
  uint64_t *mant = x->mpfr_d;
  if (i == (int64_t)0)
  {
    MPFR_Lib_mpfr_struct f0 = x[0U];
    int64_t p = f0.mpfr_prec;
    MPFR_Lib_mpfr_struct f = x[0U];
    int64_t l = (f.mpfr_prec - (int64_t)1) / MPFR_Lib_gmp_NUMB_BITS + (int64_t)1;
    mant[(uint32_t)i] = (uint64_t)0xffffffffffffffffU << (uint32_t)(l * MPFR_Lib_gmp_NUMB_BITS - p);
  }
  else
  {
    MPFR_Lib_mpfr_setmax_rec(x, i - (int64_t)1);
    mant[(uint32_t)i] = (uint64_t)0xffffffffffffffffU;
  }
}

static void MPFR_Lib_mpfr_setmax(MPFR_Lib_mpfr_struct *x)
{
  MPFR_Lib_mpfr_SET_EXP(x, MPFR_Lib_mpfr_EMAX);
  MPFR_Lib_mpfr_struct f = x[0U];
  MPFR_Lib_mpfr_setmax_rec(x, (f.mpfr_prec - (int64_t)1) / MPFR_Lib_gmp_NUMB_BITS);
}

static void MPFR_Lib_mpfr_setmin(MPFR_Lib_mpfr_struct *x)
{
  MPFR_Lib_mpfr_SET_EXP(x, MPFR_Lib_mpfr_EMIN);
  MPFR_Lib_mpfr_struct f = x[0U];
  int64_t xn = (f.mpfr_prec - (int64_t)1) / MPFR_Lib_gmp_NUMB_BITS;
  uint64_t *xp = x->mpfr_d;
  xp[(uint32_t)xn] = (uint64_t)0x8000000000000000U;
  MPFR_Lib_mpn_ZERO(xp, xn);
}

static int32_t
MPFR_Exceptions_mpfr_overflow(
  MPFR_Lib_mpfr_struct *x,
  MPFR_RoundingMode_mpfr_rnd_t rnd_mode,
  int32_t sign
)
{
  MPFR_Lib_mpfr_struct uu___55_72 = x[0U];
  x[0U] =
    (
      (MPFR_Lib_mpfr_struct){
        .mpfr_prec = uu___55_72.mpfr_prec,
        .mpfr_sign = sign,
        .mpfr_exp = uu___55_72.mpfr_exp,
        .mpfr_d = uu___55_72.mpfr_d
      }
    );
  if (MPFR_RoundingMode_mpfr_IS_LIKE_RNDZ(rnd_mode, sign < (int32_t)0))
  {
    MPFR_Lib_mpfr_setmax(x);
    return MPFR_Lib_mpfr_NEG_SIGN(sign);
  }
  else
  {
    MPFR_Lib_mpfr_SET_EXP(x, MPFR_Lib_mpfr_EXP_INF);
    return sign;
  }
}

static int32_t
MPFR_Exceptions_mpfr_underflow(
  MPFR_Lib_mpfr_struct *x,
  MPFR_RoundingMode_mpfr_rnd_t rnd_mode,
  int32_t sign
)
{
  MPFR_Lib_mpfr_struct uu___55_255 = x[0U];
  x[0U] =
    (
      (MPFR_Lib_mpfr_struct){
        .mpfr_prec = uu___55_255.mpfr_prec,
        .mpfr_sign = sign,
        .mpfr_exp = uu___55_255.mpfr_exp,
        .mpfr_d = uu___55_255.mpfr_d
      }
    );
  if (MPFR_RoundingMode_mpfr_IS_LIKE_RNDZ(rnd_mode, sign < (int32_t)0))
  {
    MPFR_Lib_mpfr_SET_EXP(x, MPFR_Lib_mpfr_EXP_ZERO);
    return MPFR_Lib_mpfr_NEG_SIGN(sign);
  }
  else
  {
    MPFR_Lib_mpfr_setmin(x);
    return sign;
  }
}

typedef struct MPFR_Add1sp1_state_s
{
  int64_t sh;
  int64_t bx;
  uint64_t rb;
  uint64_t sb;
}
MPFR_Add1sp1_state;

static MPFR_Add1sp1_state
MPFR_Add1sp1_mk_state(int64_t sh, int64_t bx, uint64_t rb, uint64_t sb)
{
  return ((MPFR_Add1sp1_state){ .sh = sh, .bx = bx, .rb = rb, .sb = sb });
}

typedef struct K___uint64_t_int64_t_s
{
  uint64_t fst;
  int64_t snd;
}
K___uint64_t_int64_t;

typedef struct K___uint64_t_uint64_t_int64_t_s
{
  uint64_t fst;
  uint64_t snd;
  int64_t thd;
}
K___uint64_t_uint64_t_int64_t;

static int32_t
MPFR_Add1sp1_mpfr_add1sp1(
  MPFR_Lib_mpfr_struct *a,
  MPFR_Lib_mpfr_struct *b,
  MPFR_Lib_mpfr_struct *c,
  MPFR_RoundingMode_mpfr_rnd_t rnd_mode,
  int64_t p
)
{
  uint64_t *ap = a->mpfr_d;
  int64_t bx = b->mpfr_exp;
  int64_t cx = c->mpfr_exp;
  uint64_t *bp = b->mpfr_d;
  uint64_t *cp = c->mpfr_d;
  int64_t sh = MPFR_Lib_gmp_NUMB_BITS - p;
  MPFR_Add1sp1_state st;
  if (bx == cx)
  {
    uint64_t a0 = (bp[0U] >> (uint32_t)1U) + (cp[0U] >> (uint32_t)1U);
    int64_t bx1 = bx + (int64_t)1;
    uint64_t rb = a0 & (uint64_t)1U << (uint32_t)(sh - (int64_t)1);
    ap[0U] = a0 ^ rb;
    uint64_t sb = (uint64_t)0U;
    st = MPFR_Add1sp1_mk_state(sh, bx1, rb, sb);
  }
  else
  {
    MPFR_Add1sp1_state ite0;
    if (bx > cx)
    {
      int64_t d = bx - cx;
      uint64_t mask = ((uint64_t)1U << (uint32_t)sh) - (uint64_t)1U;
      MPFR_Add1sp1_state ite1;
      if (d < sh)
      {
        uint64_t a0 = bp[0U] + (cp[0U] >> (uint32_t)d);
        K___uint64_t_int64_t scrut;
        if (a0 < bp[0U])
          scrut =
            (
              (K___uint64_t_int64_t){
                .fst = (uint64_t)0x8000000000000000U | a0 >> (uint32_t)1U,
                .snd = bx + (int64_t)1
              }
            );
        else
          scrut = ((K___uint64_t_int64_t){ .fst = a0, .snd = bx });
        uint64_t a01 = scrut.fst;
        int64_t bx1 = scrut.snd;
        uint64_t rb = a01 & (uint64_t)1U << (uint32_t)(sh - (int64_t)1);
        uint64_t sb = (a01 & mask) ^ rb;
        ap[0U] = a01 & ~mask;
        ite1 = MPFR_Add1sp1_mk_state(sh, bx1, rb, sb);
      }
      else
      {
        MPFR_Add1sp1_state ite;
        if (d < MPFR_Lib_gmp_NUMB_BITS)
        {
          uint64_t sb = cp[0U] << (uint32_t)(MPFR_Lib_gmp_NUMB_BITS - d);
          uint64_t a0 = bp[0U] + (cp[0U] >> (uint32_t)d);
          K___uint64_t_uint64_t_int64_t scrut;
          if (a0 < bp[0U])
            scrut =
              (
                (K___uint64_t_uint64_t_int64_t){
                  .fst = sb | (a0 & (uint64_t)1U),
                  .snd = (uint64_t)0x8000000000000000U | a0 >> (uint32_t)1U,
                  .thd = bx + (int64_t)1
                }
              );
          else
            scrut = ((K___uint64_t_uint64_t_int64_t){ .fst = sb, .snd = a0, .thd = bx });
          uint64_t sb1 = scrut.fst;
          uint64_t a01 = scrut.snd;
          int64_t bx1 = scrut.thd;
          uint64_t rb = a01 & (uint64_t)1U << (uint32_t)(sh - (int64_t)1);
          uint64_t sb2 = sb1 | ((a01 & mask) ^ rb);
          ap[0U] = a01 & ~mask;
          ite = MPFR_Add1sp1_mk_state(sh, bx1, rb, sb2);
        }
        else
        {
          ap[0U] = bp[0U];
          uint64_t rb = (uint64_t)0U;
          uint64_t sb = (uint64_t)1U;
          ite = MPFR_Add1sp1_mk_state(sh, bx, rb, sb);
        }
        ite1 = ite;
      }
      ite0 = ite1;
    }
    else
    {
      int64_t d = cx - bx;
      uint64_t mask = ((uint64_t)1U << (uint32_t)sh) - (uint64_t)1U;
      MPFR_Add1sp1_state ite1;
      if (d < sh)
      {
        uint64_t a0 = cp[0U] + (bp[0U] >> (uint32_t)d);
        K___uint64_t_int64_t scrut;
        if (a0 < cp[0U])
          scrut =
            (
              (K___uint64_t_int64_t){
                .fst = (uint64_t)0x8000000000000000U | a0 >> (uint32_t)1U,
                .snd = cx + (int64_t)1
              }
            );
        else
          scrut = ((K___uint64_t_int64_t){ .fst = a0, .snd = cx });
        uint64_t a01 = scrut.fst;
        int64_t bx1 = scrut.snd;
        uint64_t rb = a01 & (uint64_t)1U << (uint32_t)(sh - (int64_t)1);
        uint64_t sb = (a01 & mask) ^ rb;
        ap[0U] = a01 & ~mask;
        ite1 = MPFR_Add1sp1_mk_state(sh, bx1, rb, sb);
      }
      else
      {
        MPFR_Add1sp1_state ite;
        if (d < MPFR_Lib_gmp_NUMB_BITS)
        {
          uint64_t sb = bp[0U] << (uint32_t)(MPFR_Lib_gmp_NUMB_BITS - d);
          uint64_t a0 = cp[0U] + (bp[0U] >> (uint32_t)d);
          K___uint64_t_uint64_t_int64_t scrut;
          if (a0 < cp[0U])
            scrut =
              (
                (K___uint64_t_uint64_t_int64_t){
                  .fst = sb | (a0 & (uint64_t)1U),
                  .snd = (uint64_t)0x8000000000000000U | a0 >> (uint32_t)1U,
                  .thd = cx + (int64_t)1
                }
              );
          else
            scrut = ((K___uint64_t_uint64_t_int64_t){ .fst = sb, .snd = a0, .thd = cx });
          uint64_t sb1 = scrut.fst;
          uint64_t a01 = scrut.snd;
          int64_t bx1 = scrut.thd;
          uint64_t rb = a01 & (uint64_t)1U << (uint32_t)(sh - (int64_t)1);
          uint64_t sb2 = sb1 | ((a01 & mask) ^ rb);
          ap[0U] = a01 & ~mask;
          ite = MPFR_Add1sp1_mk_state(sh, bx1, rb, sb2);
        }
        else
        {
          ap[0U] = cp[0U];
          uint64_t rb = (uint64_t)0U;
          uint64_t sb = (uint64_t)1U;
          ite = MPFR_Add1sp1_mk_state(sh, cx, rb, sb);
        }
        ite1 = ite;
      }
      ite0 = ite1;
    }
    st = ite0;
  }
  if (st.bx > MPFR_Lib_mpfr_EMAX)
  {
    int32_t t = MPFR_Exceptions_mpfr_overflow(a, rnd_mode, a->mpfr_sign);
    return t;
  }
  else
  {
    uint64_t a0 = ap[0U];
    MPFR_Lib_mpfr_SET_EXP(a, st.bx);
    if (st.rb == (uint64_t)0U && st.sb == (uint64_t)0U)
      return MPFR_Lib_mpfr_RET((int32_t)0);
    else if (MPFR_RoundingMode_uu___is_MPFR_RNDN(rnd_mode))
      if
      (
        st.rb
        == (uint64_t)0U
        || (st.sb == (uint64_t)0U && (a0 & (uint64_t)1U << (uint32_t)st.sh) == (uint64_t)0U)
      )
        return MPFR_Lib_mpfr_RET(MPFR_Lib_mpfr_NEG_SIGN(a->mpfr_sign));
      else
      {
        ap[0U] = ap[0U] + ((uint64_t)1U << (uint32_t)st.sh);
        if (ap[0U] == (uint64_t)0U)
        {
          ap[0U] = (uint64_t)0x8000000000000000U;
          if (st.bx + (int64_t)1 <= MPFR_Lib_mpfr_EMAX)
          {
            MPFR_Lib_mpfr_SET_EXP(a, st.bx + (int64_t)1);
            return MPFR_Lib_mpfr_RET(a->mpfr_sign);
          }
          else
          {
            int32_t t = MPFR_Exceptions_mpfr_overflow(a, rnd_mode, a->mpfr_sign);
            return MPFR_Lib_mpfr_RET(t);
          }
        }
        else
          return MPFR_Lib_mpfr_RET(a->mpfr_sign);
      }
    else if (MPFR_RoundingMode_mpfr_IS_LIKE_RNDZ(rnd_mode, a->mpfr_sign < (int32_t)0))
      return MPFR_Lib_mpfr_RET(MPFR_Lib_mpfr_NEG_SIGN(a->mpfr_sign));
    else
    {
      ap[0U] = ap[0U] + ((uint64_t)1U << (uint32_t)st.sh);
      if (ap[0U] == (uint64_t)0U)
      {
        ap[0U] = (uint64_t)0x8000000000000000U;
        if (st.bx + (int64_t)1 <= MPFR_Lib_mpfr_EMAX)
        {
          MPFR_Lib_mpfr_SET_EXP(a, st.bx + (int64_t)1);
          return MPFR_Lib_mpfr_RET(a->mpfr_sign);
        }
        else
        {
          int32_t t = MPFR_Exceptions_mpfr_overflow(a, rnd_mode, a->mpfr_sign);
          return MPFR_Lib_mpfr_RET(t);
        }
      }
      else
        return MPFR_Lib_mpfr_RET(a->mpfr_sign);
    }
  }
}

typedef struct K___uint64_t_uint64_t_s
{
  uint64_t fst;
  uint64_t snd;
}
K___uint64_t_uint64_t;

static K___uint64_t_uint64_t MPFR_Umul_ppmm_umul_ppmm(uint64_t m, uint64_t n1)
{
  FStar_UInt128_uint128 p = FStar_UInt128_mul_wide(m, n1);
  return
    (
      (K___uint64_t_uint64_t){
        .fst = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(p, (uint32_t)64U)),
        .snd = FStar_UInt128_uint128_to_uint64(p)
      }
    );
}

typedef struct K___int64_t_uint64_t_uint64_t_s
{
  int64_t fst;
  uint64_t snd;
  uint64_t thd;
}
K___int64_t_uint64_t_uint64_t;

static int32_t
MPFR_Mul_1_mpfr_mul_1(
  MPFR_Lib_mpfr_struct *a,
  MPFR_Lib_mpfr_struct *b,
  MPFR_Lib_mpfr_struct *c,
  MPFR_RoundingMode_mpfr_rnd_t rnd_mode,
  int64_t p
)
{
  uint64_t *ap = a->mpfr_d;
  uint64_t *bp = b->mpfr_d;
  uint64_t *cp = c->mpfr_d;
  uint64_t b0 = bp[0U];
  uint64_t c0 = cp[0U];
  int64_t sh = MPFR_Lib_gmp_NUMB_BITS - p;
  uint64_t mask = ((uint64_t)1U << (uint32_t)sh) - (uint64_t)1U;
  int64_t ax = b->mpfr_exp + c->mpfr_exp;
  K___uint64_t_uint64_t scrut0 = MPFR_Umul_ppmm_umul_ppmm(b0, c0);
  uint64_t a0 = scrut0.fst;
  uint64_t sb = scrut0.snd;
  K___int64_t_uint64_t_uint64_t scrut;
  if (a0 < (uint64_t)0x8000000000000000U)
    scrut =
      (
        (K___int64_t_uint64_t_uint64_t){
          .fst = ax - (int64_t)1,
          .snd = a0 << (uint32_t)1U | sb >> (uint32_t)(MPFR_Lib_gmp_NUMB_BITS - (int64_t)1),
          .thd = sb << (uint32_t)1U
        }
      );
  else
    scrut = ((K___int64_t_uint64_t_uint64_t){ .fst = ax, .snd = a0, .thd = sb });
  int64_t ax1 = scrut.fst;
  uint64_t a01 = scrut.snd;
  uint64_t sb1 = scrut.thd;
  uint64_t rb = a01 & (uint64_t)1U << (uint32_t)(sh - (int64_t)1);
  uint64_t sb2 = sb1 | ((a01 & mask) ^ rb);
  ap[0U] = a01 & ~mask;
  MPFR_Lib_mpfr_struct uu___55_2514 = a[0U];
  a[0U] =
    (
      (MPFR_Lib_mpfr_struct){
        .mpfr_prec = uu___55_2514.mpfr_prec,
        .mpfr_sign = b->mpfr_sign * c->mpfr_sign,
        .mpfr_exp = uu___55_2514.mpfr_exp,
        .mpfr_d = uu___55_2514.mpfr_d
      }
    );
  uint64_t *ap1 = a->mpfr_d;
  uint64_t a02 = ap1[0U];
  if (ax1 > MPFR_Lib_mpfr_EMAX)
    return MPFR_Exceptions_mpfr_overflow(a, rnd_mode, a->mpfr_sign);
  else if (ax1 < MPFR_Lib_mpfr_EMIN)
  {
    bool aneg = a->mpfr_sign < (int32_t)0;
    if
    (
      ax1
      == MPFR_Lib_mpfr_EMIN - (int64_t)1
      && a02 == ~mask
      &&
        ((MPFR_RoundingMode_uu___is_MPFR_RNDN(rnd_mode) && rb > (uint64_t)0U)
        || ((rb | sb2) > (uint64_t)0U && MPFR_RoundingMode_mpfr_IS_LIKE_RNDA(rnd_mode, aneg)))
    )
    {
      uint64_t *ap2 = a->mpfr_d;
      uint64_t a03 = ap2[0U];
      MPFR_Lib_mpfr_SET_EXP(a, ax1);
      if (rb == (uint64_t)0U && sb2 == (uint64_t)0U)
        return MPFR_Lib_mpfr_RET((int32_t)0);
      else if (MPFR_RoundingMode_uu___is_MPFR_RNDN(rnd_mode))
        if
        (
          rb
          == (uint64_t)0U
          || (sb2 == (uint64_t)0U && (a03 & (uint64_t)1U << (uint32_t)sh) == (uint64_t)0U)
        )
          return MPFR_Lib_mpfr_RET(MPFR_Lib_mpfr_NEG_SIGN(a->mpfr_sign));
        else
        {
          uint64_t *ap3 = a->mpfr_d;
          ap3[0U] = ap3[0U] + ((uint64_t)1U << (uint32_t)sh);
          if (ap3[0U] == (uint64_t)0U)
          {
            ap3[0U] = (uint64_t)0x8000000000000000U;
            if (ax1 + (int64_t)1 > MPFR_Lib_mpfr_EMAX)
              return MPFR_Exceptions_mpfr_overflow(a, rnd_mode, a->mpfr_sign);
            else
            {
              MPFR_Lib_mpfr_SET_EXP(a, ax1 + (int64_t)1);
              return MPFR_Lib_mpfr_RET(a->mpfr_sign);
            }
          }
          else
            return MPFR_Lib_mpfr_RET(a->mpfr_sign);
        }
      else if (MPFR_RoundingMode_mpfr_IS_LIKE_RNDZ(rnd_mode, a->mpfr_sign < (int32_t)0))
        return MPFR_Lib_mpfr_RET(MPFR_Lib_mpfr_NEG_SIGN(a->mpfr_sign));
      else
      {
        uint64_t *ap3 = a->mpfr_d;
        ap3[0U] = ap3[0U] + ((uint64_t)1U << (uint32_t)sh);
        if (ap3[0U] == (uint64_t)0U)
        {
          ap3[0U] = (uint64_t)0x8000000000000000U;
          if (ax1 + (int64_t)1 > MPFR_Lib_mpfr_EMAX)
            return MPFR_Exceptions_mpfr_overflow(a, rnd_mode, a->mpfr_sign);
          else
          {
            MPFR_Lib_mpfr_SET_EXP(a, ax1 + (int64_t)1);
            return MPFR_Lib_mpfr_RET(a->mpfr_sign);
          }
        }
        else
          return MPFR_Lib_mpfr_RET(a->mpfr_sign);
      }
    }
    else if
    (
      MPFR_RoundingMode_uu___is_MPFR_RNDN(rnd_mode)
      &&
        (ax1
        < MPFR_Lib_mpfr_EMIN - (int64_t)1
        || (a02 == (uint64_t)0x8000000000000000U && (rb | sb2) == (uint64_t)0U))
    )
      return MPFR_Exceptions_mpfr_underflow(a, MPFR_RoundingMode_MPFR_RNDZ, a->mpfr_sign);
    else
      return MPFR_Exceptions_mpfr_underflow(a, rnd_mode, a->mpfr_sign);
  }
  else
  {
    uint64_t *ap2 = a->mpfr_d;
    uint64_t a03 = ap2[0U];
    MPFR_Lib_mpfr_SET_EXP(a, ax1);
    if (rb == (uint64_t)0U && sb2 == (uint64_t)0U)
      return MPFR_Lib_mpfr_RET((int32_t)0);
    else if (MPFR_RoundingMode_uu___is_MPFR_RNDN(rnd_mode))
      if
      (
        rb
        == (uint64_t)0U
        || (sb2 == (uint64_t)0U && (a03 & (uint64_t)1U << (uint32_t)sh) == (uint64_t)0U)
      )
        return MPFR_Lib_mpfr_RET(MPFR_Lib_mpfr_NEG_SIGN(a->mpfr_sign));
      else
      {
        uint64_t *ap3 = a->mpfr_d;
        ap3[0U] = ap3[0U] + ((uint64_t)1U << (uint32_t)sh);
        if (ap3[0U] == (uint64_t)0U)
        {
          ap3[0U] = (uint64_t)0x8000000000000000U;
          if (ax1 + (int64_t)1 > MPFR_Lib_mpfr_EMAX)
            return MPFR_Exceptions_mpfr_overflow(a, rnd_mode, a->mpfr_sign);
          else
          {
            MPFR_Lib_mpfr_SET_EXP(a, ax1 + (int64_t)1);
            return MPFR_Lib_mpfr_RET(a->mpfr_sign);
          }
        }
        else
          return MPFR_Lib_mpfr_RET(a->mpfr_sign);
      }
    else if (MPFR_RoundingMode_mpfr_IS_LIKE_RNDZ(rnd_mode, a->mpfr_sign < (int32_t)0))
      return MPFR_Lib_mpfr_RET(MPFR_Lib_mpfr_NEG_SIGN(a->mpfr_sign));
    else
    {
      uint64_t *ap3 = a->mpfr_d;
      ap3[0U] = ap3[0U] + ((uint64_t)1U << (uint32_t)sh);
      if (ap3[0U] == (uint64_t)0U)
      {
        ap3[0U] = (uint64_t)0x8000000000000000U;
        if (ax1 + (int64_t)1 > MPFR_Lib_mpfr_EMAX)
          return MPFR_Exceptions_mpfr_overflow(a, rnd_mode, a->mpfr_sign);
        else
        {
          MPFR_Lib_mpfr_SET_EXP(a, ax1 + (int64_t)1);
          return MPFR_Lib_mpfr_RET(a->mpfr_sign);
        }
      }
      else
        return MPFR_Lib_mpfr_RET(a->mpfr_sign);
    }
  }
}

int32_t
(*MPFR_mpfr_add1sp1)(
  MPFR_Lib_mpfr_struct *x0,
  MPFR_Lib_mpfr_struct *x1,
  MPFR_Lib_mpfr_struct *x2,
  MPFR_RoundingMode_mpfr_rnd_t x3,
  int64_t x4
) = MPFR_Add1sp1_mpfr_add1sp1;

int32_t
(*MPFR_mpfr_mul_1)(
  MPFR_Lib_mpfr_struct *x0,
  MPFR_Lib_mpfr_struct *x1,
  MPFR_Lib_mpfr_struct *x2,
  MPFR_RoundingMode_mpfr_rnd_t x3,
  int64_t x4
) = MPFR_Mul_1_mpfr_mul_1;

