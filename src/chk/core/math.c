#include <chk/core/math.h>

#include <math.h>

CORE_API F32 DegToRad_F32(F32 deg) { return deg * (Pi32 / 180.0f); }
CORE_API F64 DegToRad_F64(F64 deg) { return deg * (Pi64 / 180.0); }

CORE_API F32 RadToDeg_F32(F32 rad) { return rad * (180.0f / Pi32); }
CORE_API F64 RadToDeg_F64(F64 rad) { return rad * (180.0 / Pi64); }

CORE_API F32 Sin_F32(F32 rad) { return sinf(rad); }
CORE_API F64 Sin_F64(F64 rad) { return sin(rad); }

CORE_API F32 Cos_F32(F32 rad) { return cosf(rad); }
CORE_API F64 Cos_F64(F64 rad) { return cos(rad); }

CORE_API F32 Tan_F32(F32 rad) { return tanf(rad); }
CORE_API F64 Tan_F64(F64 rad) { return tan(rad); }

CORE_API F32 ASin_F32(F32 val) { return asinf(val); }
CORE_API F64 ASin_F64(F64 val) { return asin(val); }

CORE_API F32 ACos_F32(F32 val) { return acosf(val); }
CORE_API F64 ACos_F64(F64 val) { return acos(val); }

CORE_API F32 ATan_F32(F32 val) { return atanf(val); }
CORE_API F64 ATan_F64(F64 val) { return atan(val); }

CORE_API F32 ATan2_F32(F32 y, F32 x) { return atan2f(y, x); }
CORE_API F64 ATan2_F64(F64 y, F64 x) { return atan2(y, x); }

CORE_API F32 Sqrt_F32(F32 val) { return sqrtf(val); }
CORE_API F64 Sqrt_F64(F64 val) { return sqrt(val); }

CORE_API F32 Pow_F32(F32 base, F32 exp) { return powf(base, exp); }
CORE_API F64 Pow_F64(F64 base, F64 exp) { return pow(base, exp); }

CORE_API F32 Exp_F32(F32 val) { return expf(val); }
CORE_API F64 Exp_F64(F64 val) { return exp(val); }

CORE_API F32 Floor_F32(F32 val) { return floorf(val); }
CORE_API F64 Floor_F64(F64 val) { return floor(val); }

CORE_API F32 Ceil_F32(F32 val) { return ceilf(val); }
CORE_API F64 Ceil_F64(F64 val) { return ceil(val); }

CORE_API F32 Round_F32(F32 val) { return roundf(val); }
CORE_API F64 Round_F64(F64 val) { return round(val); }

CORE_API S8  Sign_S8(F32 val) { return (S8)((val > 0.0f) - (val < 0.0f)); }
CORE_API S16 Sign_S16(F32 val) { return (S16)((val > 0.0f) - (val < 0.0f)); }
CORE_API S32 Sign_S32(F32 val) { return (S32)((val > 0.0f) - (val < 0.0f)); }
CORE_API S64 Sign_S64(F32 val) { return (S64)((val > 0.0f) - (val < 0.0f)); }
CORE_API F32 Sign_F32(F32 val) { return (F32)((val > 0.0f) - (val < 0.0f)); }
CORE_API F64 Sign_F64(F64 val) { return (F64)((val > 0.0f) - (val < 0.0f)); }

CORE_API S8  Abs_S8(S8 val) { return (val < 0) ? -val : val; }
CORE_API S16 Abs_S16(S16 val) { return (val < 0) ? -val : val; }
CORE_API S32 Abs_S32(S32 val) { return (val < 0) ? -val : val; }
CORE_API S64 Abs_S64(S64 val) { return (val < 0) ? -val : val; }
CORE_API F32 Abs_F32(F32 val) { return (val < 0.0f) ? -val : val; }
CORE_API F64 Abs_F64(F64 val) { return (val < 0.0) ? -val : val; }

CORE_API U8  Min_U8(U8 a, U8 b) { return (a < b) ? a : b; }
CORE_API U16 Min_U16(U16 a, U16 b) { return (a < b) ? a : b; }
CORE_API U32 Min_U32(U32 a, U32 b) { return (a < b) ? a : b; }
CORE_API U64 Min_U64(U64 a, U64 b) { return (a < b) ? a : b; }
CORE_API S8  Min_S8(S8 a, S8 b) { return (a < b) ? a : b; }
CORE_API S16 Min_S16(S16 a, S16 b) { return (a < b) ? a : b; }
CORE_API S32 Min_S32(S32 a, S32 b) { return (a < b) ? a : b; }
CORE_API S64 Min_S64(S64 a, S64 b) { return (a < b) ? a : b; }
CORE_API F32 Min_F32(F32 a, F32 b) { return fminf(a, b); }
CORE_API F64 Min_F64(F64 a, F64 b) { return fmin(a, b); }

CORE_API U8  Max_U8(U8 a, U8 b) { return (a > b) ? a : b; }
CORE_API U16 Max_U16(U16 a, U16 b) { return (a > b) ? a : b; }
CORE_API U32 Max_U32(U32 a, U32 b) { return (a > b) ? a : b; }
CORE_API U64 Max_U64(U64 a, U64 b) { return (a > b) ? a : b; }
CORE_API S8  Max_S8(S8 a, S8 b) { return (a > b) ? a : b; }
CORE_API S16 Max_S16(S16 a, S16 b) { return (a > b) ? a : b; }
CORE_API S32 Max_S32(S32 a, S32 b) { return (a > b) ? a : b; }
CORE_API S64 Max_S64(S64 a, S64 b) { return (a > b) ? a : b; }
CORE_API F32 Max_F32(F32 a, F32 b) { return fmaxf(a, b); }
CORE_API F64 Max_F64(F64 a, F64 b) { return fmax(a, b); }

CORE_API U8  Clamp_U8(U8 val, U8 min, U8 max) { return Min(Max(val, min), max); }
CORE_API U16 Clamp_U16(U16 val, U16 min, U16 max) { return Min(Max(val, min), max); }
CORE_API U32 Clamp_U32(U32 val, U32 min, U32 max) { return Min(Max(val, min), max); }
CORE_API U64 Clamp_U64(U64 val, U64 min, U64 max) { return Min(Max(val, min), max); }
CORE_API S8  Clamp_S8(S8 val, S8 min, S8 max) { return Min(Max(val, min), max); }
CORE_API S16 Clamp_S16(S16 val, S16 min, S16 max) { return Min(Max(val, min), max); }
CORE_API S32 Clamp_S32(S32 val, S32 min, S32 max) { return Min(Max(val, min), max); }
CORE_API S64 Clamp_S64(S64 val, S64 min, S64 max) { return Min(Max(val, min), max); }
CORE_API F32 Clamp_F32(F32 val, F32 min, F32 max) { return Min(Max(val, min), max); }
CORE_API F64 Clamp_F64(F64 val, F64 min, F64 max) { return Min(Max(val, min), max); }

CORE_API U8  Lerp_U8(U8 a, U8 b, F32 t) { return (U8)Lerp_F32((F32)a, (F32)b, t); }
CORE_API U16 Lerp_U16(U16 a, U16 b, F32 t) { return (U16)Lerp_F32((F32)a, (F32)b, t); }
CORE_API U32 Lerp_U32(U32 a, U32 b, F32 t) { return (U32)Lerp_F32((F32)a, (F32)b, t); }
CORE_API U64 Lerp_U64(U64 a, U64 b, F32 t) { return (U64)Lerp_F64((F64)a, (F64)b, t); }
CORE_API S8  Lerp_S8(S8 a, S8 b, F32 t) { return (S8)Lerp_F32((F32)a, (F32)b, t); }
CORE_API S16 Lerp_S16(S16 a, S16 b, F32 t) { return (S16)Lerp_F32((F32)a, (F32)b, t); }
CORE_API S32 Lerp_S32(S32 a, S32 b, F32 t) { return (S32)Lerp_F32((F32)a, (F32)b, t); }
CORE_API S64 Lerp_S64(S64 a, S64 b, F32 t) { return (S64)Lerp_F64((F64)a, (F64)b, t); }
CORE_API F32 Lerp_F32(F32 a, F32 b, F32 t) { return a + (b - a) * t; }
CORE_API F64 Lerp_F64(F64 a, F64 b, F64 t) { return a + (b - a) * t; }
