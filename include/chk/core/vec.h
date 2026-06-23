#pragma once

#include <chk/core/api.h>

#include <chk/core/types.h>

typedef union V2 {
  struct {
    F32 x, y;
  };
  struct {
    F32 w, h;
  };
  struct {
    F32 u, v;
  };
  F32 _raw[2];
} V2;

typedef union V3 {
  struct {
    F32 x, y, z;
  };
  struct {
    F32 r, g, b;
  };
  F32 _raw[3];
} V3;

typedef union V4 {
  struct {
    F32 x, y, z, w;
  };
  struct {
    F32 r, g, b, a;
  };
  struct {
    V2 pos, size;
  };
  F32 _raw[4];
} V4;

CORE_API V2 V2_Make(F32 x, F32 y);
CORE_API V3 V3_Make(F32 x, F32 y, F32 z);
CORE_API V4 V4_Make(F32 x, F32 y, F32 z, F32 w);

CORE_API B8 V2_Equals(V2 a, V2 b);
CORE_API B8 V3_Equals(V3 a, V3 b);
CORE_API B8 V4_Equals(V4 a, V4 b);

CORE_API V2 V2_Neg(V2 v);
CORE_API V3 V3_Neg(V3 v);
CORE_API V4 V4_Neg(V4 v);

CORE_API V2 V2_Add(V2 a, V2 b);
CORE_API V3 V3_Add(V3 a, V3 b);
CORE_API V4 V4_Add(V4 a, V4 b);

CORE_API V2 V2_Sub(V2 a, V2 b);
CORE_API V3 V3_Sub(V3 a, V3 b);
CORE_API V4 V4_Sub(V4 a, V4 b);

CORE_API V2 V2_Mul(V2 a, V2 b);
CORE_API V3 V3_Mul(V3 a, V3 b);
CORE_API V4 V4_Mul(V4 a, V4 b);

CORE_API V2 V2_Div(V2 a, V2 b);
CORE_API V3 V3_Div(V3 a, V3 b);
CORE_API V4 V4_Div(V4 a, V4 b);

CORE_API V2 V2_Scale(V2 v, F32 s);
CORE_API V3 V3_Scale(V3 v, F32 s);
CORE_API V4 V4_Scale(V4 v, F32 s);

CORE_API V2 V2_InvScale(V2 v, F32 s);
CORE_API V3 V3_InvScale(V3 v, F32 s);
CORE_API V4 V4_InvScale(V4 v, F32 s);

CORE_API V2 V2_Normalized(V2 v);
CORE_API V3 V3_Normalized(V3 v);
CORE_API V4 V4_Normalized(V4 v);

CORE_API V2 V2_Lerp(V2 a, V2 b, F32 t);
CORE_API V3 V3_Lerp(V3 a, V3 b, F32 t);
CORE_API V4 V4_Lerp(V4 a, V4 b, F32 t);

CORE_API V3 V3_Cross(V3 a, V3 b);

CORE_API F32 V2_Dot(V2 a, V2 b);
CORE_API F32 V3_Dot(V3 a, V3 b);
CORE_API F32 V4_Dot(V4 a, V4 b);

CORE_API F32 V2_LenSq(V2 v);
CORE_API F32 V3_LenSq(V3 v);
CORE_API F32 V4_LenSq(V4 v);

CORE_API F32 V2_Len(V2 v);
CORE_API F32 V3_Len(V3 v);
CORE_API F32 V4_Len(V4 v);

CORE_API F32 V2_DistSq(V2 a, V2 b);
CORE_API F32 V3_DistSq(V3 a, V3 b);
CORE_API F32 V4_DistSq(V4 a, V4 b);

CORE_API F32 V2_Dist(V2 a, V2 b);
CORE_API F32 V3_Dist(V3 a, V3 b);
CORE_API F32 V4_Dist(V4 a, V4 b);
