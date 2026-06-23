#pragma once

#include <chk/core/api.h>

#include <chk/core/types.h>

#define Pi32 3.14159265358979323846f
#define Pi64 3.14159265358979323846

CORE_API F32 DegToRad_F32(F32 deg);
CORE_API F64 DegToRad_F64(F64 deg);

CORE_API F32 RadToDeg_F32(F32 rad);
CORE_API F64 RadToDeg_F64(F64 rad);

#define DegToRad(deg) _Generic((deg), F32: DegToRad_F32, F64: DegToRad_F64)(deg)
#define RadToDeg(rad) _Generic((rad), F32: RadToDeg_F32, F64: RadToDeg_F64)(rad)

CORE_API F32 Sin_F32(F32 rad);
CORE_API F64 Sin_F64(F64 rad);

CORE_API F32 Cos_F32(F32 rad);
CORE_API F64 Cos_F64(F64 rad);

CORE_API F32 Tan_F32(F32 rad);
CORE_API F64 Tan_F64(F64 rad);

CORE_API F32 ASin_F32(F32 val);
CORE_API F64 ASin_F64(F64 val);

CORE_API F32 ACos_F32(F32 val);
CORE_API F64 ACos_F64(F64 val);

CORE_API F32 ATan_F32(F32 val);
CORE_API F64 ATan_F64(F64 val);

CORE_API F32 ATan2_F32(F32 y, F32 x);
CORE_API F64 ATan2_F64(F64 y, F64 x);

#define Sin(rad)    _Generic((rad), F32: Sin_F32, F64: Sin_F64)(rad)
#define Cos(rad)    _Generic((rad), F32: Cos_F32, F64: Cos_F64)(rad)
#define Tan(rad)    _Generic((rad), F32: Tan_F32, F64: Tan_F64)(rad)
#define ASin(val)   _Generic((val), F32: ASin_F32, F64: ASin_F64)(val)
#define ACos(val)   _Generic((val), F32: ACos_F32, F64: ACos_F64)(val)
#define ATan(val)   _Generic((val), F32: ATan_F32, F64: ATan_F64)(val)
#define ATan2(y, x) _Generic((y), F32: ATan2_F32, F64: ATan2_F64)(y, x)

CORE_API F32 Sqrt_F32(F32 val);
CORE_API F64 Sqrt_F64(F64 val);

CORE_API F32 Pow_F32(F32 base, F32 exp);
CORE_API F64 Pow_F64(F64 base, F64 exp);

CORE_API F32 Exp_F32(F32 val);
CORE_API F64 Exp_F64(F64 val);

#define Sqrt(val)      _Generic((val), F32: Sqrt_F32, F64: Sqrt_F64)(val)
#define Pow(base, exp) _Generic((base), F32: Pow_F32, F64: Pow_F64)(base, exp)
#define Exp(val)       _Generic((val), F32: Exp_F32, F64: Exp_F64)(val)

CORE_API F32 Floor_F32(F32 val);
CORE_API F64 Floor_F64(F64 val);

CORE_API F32 Ceil_F32(F32 val);
CORE_API F64 Ceil_F64(F64 val);

CORE_API F32 Round_F32(F32 val);
CORE_API F64 Round_F64(F64 val);

#define Floor(val) _Generic((val), F32: Floor_F32, F64: Floor_F64)(val)
#define Ceil(val)  _Generic((val), F32: Ceil_F32, F64: Ceil_F64)(val)
#define Round(val) _Generic((val), F32: Round_F32, F64: Round_F64)(val)

CORE_API S8  Sign_S8(F32 val);
CORE_API S16 Sign_S16(F32 val);
CORE_API S32 Sign_S32(F32 val);
CORE_API S64 Sign_S64(F32 val);
CORE_API F32 Sign_F32(F32 val);
CORE_API F64 Sign_F64(F64 val);

CORE_API S8  Abs_S8(S8 val);
CORE_API S16 Abs_S16(S16 val);
CORE_API S32 Abs_S32(S32 val);
CORE_API S64 Abs_S64(S64 val);
CORE_API F32 Abs_F32(F32 val);
CORE_API F64 Abs_F64(F64 val);

#define Sign(val)                                                                                                      \
  _Generic((val), S8: Sign_S8, S16: Sign_S16, S32: Sign_S32, S64: Sign_S64, F32: Sign_F32, F64: Sign_F64)(val)
#define Abs(val) _Generic((val), S8: Abs_S8, S16: Abs_S16, S32: Abs_S32, S64: Abs_S64, F32: Abs_F32, F64: Abs_F64)(val)

CORE_API U8  Min_U8(U8 a, U8 b);
CORE_API U16 Min_U16(U16 a, U16 b);
CORE_API U32 Min_U32(U32 a, U32 b);
CORE_API U64 Min_U64(U64 a, U64 b);
CORE_API S8  Min_S8(S8 a, S8 b);
CORE_API S16 Min_S16(S16 a, S16 b);
CORE_API S32 Min_S32(S32 a, S32 b);
CORE_API S64 Min_S64(S64 a, S64 b);
CORE_API F32 Min_F32(F32 a, F32 b);
CORE_API F64 Min_F64(F64 a, F64 b);

CORE_API U8  Max_U8(U8 a, U8 b);
CORE_API U16 Max_U16(U16 a, U16 b);
CORE_API U32 Max_U32(U32 a, U32 b);
CORE_API U64 Max_U64(U64 a, U64 b);
CORE_API S8  Max_S8(S8 a, S8 b);
CORE_API S16 Max_S16(S16 a, S16 b);
CORE_API S32 Max_S32(S32 a, S32 b);
CORE_API S64 Max_S64(S64 a, S64 b);
CORE_API F32 Max_F32(F32 a, F32 b);
CORE_API F64 Max_F64(F64 a, F64 b);

CORE_API U8  Clamp_U8(U8 val, U8 min, U8 max);
CORE_API U16 Clamp_U16(U16 val, U16 min, U16 max);
CORE_API U32 Clamp_U32(U32 val, U32 min, U32 max);
CORE_API U64 Clamp_U64(U64 val, U64 min, U64 max);
CORE_API S8  Clamp_S8(S8 val, S8 min, S8 max);
CORE_API S16 Clamp_S16(S16 val, S16 min, S16 max);
CORE_API S32 Clamp_S32(S32 val, S32 min, S32 max);
CORE_API S64 Clamp_S64(S64 val, S64 min, S64 max);
CORE_API F32 Clamp_F32(F32 val, F32 min, F32 max);
CORE_API F64 Clamp_F64(F64 val, F64 min, F64 max);

CORE_API U8  Lerp_U8(U8 a, U8 b, F32 t);
CORE_API U16 Lerp_U16(U16 a, U16 b, F32 t);
CORE_API U32 Lerp_U32(U32 a, U32 b, F32 t);
CORE_API U64 Lerp_U64(U64 a, U64 b, F32 t);
CORE_API S8  Lerp_S8(S8 a, S8 b, F32 t);
CORE_API S16 Lerp_S16(S16 a, S16 b, F32 t);
CORE_API S32 Lerp_S32(S32 a, S32 b, F32 t);
CORE_API S64 Lerp_S64(S64 a, S64 b, F32 t);
CORE_API F32 Lerp_F32(F32 a, F32 b, F32 t);
CORE_API F64 Lerp_F64(F64 a, F64 b, F64 t);

#define Min(a, b)                                                                                                      \
  _Generic((a),                                                                                                        \
      U8: Min_U8,                                                                                                      \
      U16: Min_U16,                                                                                                    \
      U32: Min_U32,                                                                                                    \
      U64: Min_U64,                                                                                                    \
      S8: Min_S8,                                                                                                      \
      S16: Min_S16,                                                                                                    \
      S32: Min_S32,                                                                                                    \
      S64: Min_S64,                                                                                                    \
      F32: Min_F32,                                                                                                    \
      F64: Min_F64)(a, b)
#define Max(a, b)                                                                                                      \
  _Generic((a),                                                                                                        \
      U8: Max_U8,                                                                                                      \
      U16: Max_U16,                                                                                                    \
      U32: Max_U32,                                                                                                    \
      U64: Max_U64,                                                                                                    \
      S8: Max_S8,                                                                                                      \
      S16: Max_S16,                                                                                                    \
      S32: Max_S32,                                                                                                    \
      S64: Max_S64,                                                                                                    \
      F32: Max_F32,                                                                                                    \
      F64: Max_F64)(a, b)
#define Clamp(val, min, max)                                                                                           \
  _Generic((val),                                                                                                      \
      U8: Clamp_U8,                                                                                                    \
      U16: Clamp_U16,                                                                                                  \
      U32: Clamp_U32,                                                                                                  \
      U64: Clamp_U64,                                                                                                  \
      S8: Clamp_S8,                                                                                                    \
      S16: Clamp_S16,                                                                                                  \
      S32: Clamp_S32,                                                                                                  \
      S64: Clamp_S64,                                                                                                  \
      F32: Clamp_F32,                                                                                                  \
      F64: Clamp_F64)(val, min, max)
#define Lerp(a, b, t)                                                                                                  \
  _Generic((a),                                                                                                        \
      U8: Lerp_U8,                                                                                                     \
      U16: Lerp_U16,                                                                                                   \
      U32: Lerp_U32,                                                                                                   \
      U64: Lerp_U64,                                                                                                   \
      S8: Lerp_S8,                                                                                                     \
      S16: Lerp_S16,                                                                                                   \
      S32: Lerp_S32,                                                                                                   \
      S64: Lerp_S64,                                                                                                   \
      F32: Lerp_F32,                                                                                                   \
      F64: Lerp_F64)(a, b, t)
