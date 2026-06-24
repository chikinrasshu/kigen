#pragma once

#include <chk/core/api.h>

#include <chk/core/types.h>

typedef struct RGBA {
  F32 r, g, b, a;
} RGBA;

typedef struct HSLA {
  F32 h, s, l, a;
} HSLA;

CORE_API RGBA RGBA_FromHSLA(HSLA hsla);
CORE_API HSLA HSLA_FromRGBA(RGBA rgba);

CORE_API RGBA RGBA_FromHex(U32 hex);
CORE_API U32  RGBA_ToHex(RGBA rgba);

CORE_API RGBA RGBA_Lerp(RGBA a, RGBA b, F32 t);
CORE_API HSLA HSLA_Lerp(HSLA a, HSLA b, F32 t);
