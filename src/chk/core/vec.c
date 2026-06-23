#include <chk/core/vec.h>

#include <chk/core/math.h>

CORE_API V2 V2_Make(F32 x, F32 y) { return (V2){x, y}; }
CORE_API V3 V3_Make(F32 x, F32 y, F32 z) { return (V3){x, y, z}; }
CORE_API V4 V4_Make(F32 x, F32 y, F32 z, F32 w) { return (V4){x, y, z, w}; }

CORE_API B8 V2_Equals(V2 a, V2 b) { return a.x == b.x && a.y == b.y; }
CORE_API B8 V3_Equals(V3 a, V3 b) { return a.x == b.x && a.y == b.y && a.z == b.z; }
CORE_API B8 V4_Equals(V4 a, V4 b) { return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w; }

CORE_API V2 V2_Neg(V2 v) { return (V2){-v.x, -v.y}; }
CORE_API V3 V3_Neg(V3 v) { return (V3){-v.x, -v.y, -v.z}; }
CORE_API V4 V4_Neg(V4 v) { return (V4){-v.x, -v.y, -v.z, -v.w}; }

CORE_API V2 V2_Add(V2 a, V2 b) { return (V2){a.x + b.x, a.y + b.y}; }
CORE_API V3 V3_Add(V3 a, V3 b) { return (V3){a.x + b.x, a.y + b.y, a.z + b.z}; }
CORE_API V4 V4_Add(V4 a, V4 b) { return (V4){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w}; }

CORE_API V2 V2_Sub(V2 a, V2 b) { return (V2){a.x - b.x, a.y - b.y}; }
CORE_API V3 V3_Sub(V3 a, V3 b) { return (V3){a.x - b.x, a.y - b.y, a.z - b.z}; }
CORE_API V4 V4_Sub(V4 a, V4 b) { return (V4){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w}; }

CORE_API V2 V2_Mul(V2 a, V2 b) { return (V2){a.x * b.x, a.y * b.y}; }
CORE_API V3 V3_Mul(V3 a, V3 b) { return (V3){a.x * b.x, a.y * b.y, a.z * b.z}; }
CORE_API V4 V4_Mul(V4 a, V4 b) { return (V4){a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w}; }

CORE_API V2 V2_Div(V2 a, V2 b) { return (V2){a.x / b.x, a.y / b.y}; }
CORE_API V3 V3_Div(V3 a, V3 b) { return (V3){a.x / b.x, a.y / b.y, a.z / b.z}; }
CORE_API V4 V4_Div(V4 a, V4 b) { return (V4){a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w}; }

CORE_API V2 V2_Scale(V2 v, F32 s) { return (V2){v.x * s, v.y * s}; }
CORE_API V3 V3_Scale(V3 v, F32 s) { return (V3){v.x * s, v.y * s, v.z * s}; }
CORE_API V4 V4_Scale(V4 v, F32 s) { return (V4){v.x * s, v.y * s, v.z * s, v.w * s}; }

CORE_API V2 V2_InvScale(V2 v, F32 s) { return (V2){v.x / s, v.y / s}; }
CORE_API V3 V3_InvScale(V3 v, F32 s) { return (V3){v.x / s, v.y / s, v.z / s}; }
CORE_API V4 V4_InvScale(V4 v, F32 s) { return (V4){v.x / s, v.y / s, v.z / s, v.w / s}; }

CORE_API V2 V2_Normalized(V2 v) { return V2_InvScale(v, V2_Len(v)); }
CORE_API V3 V3_Normalized(V3 v) { return V3_InvScale(v, V3_Len(v)); }
CORE_API V4 V4_Normalized(V4 v) { return V4_InvScale(v, V4_Len(v)); }

CORE_API V2 V2_Lerp(V2 a, V2 b, F32 t) { return V2_Add(a, V2_Scale(V2_Sub(b, a), t)); }
CORE_API V3 V3_Lerp(V3 a, V3 b, F32 t) { return V3_Add(a, V3_Scale(V3_Sub(b, a), t)); }
CORE_API V4 V4_Lerp(V4 a, V4 b, F32 t) { return V4_Add(a, V4_Scale(V4_Sub(b, a), t)); }

CORE_API V3 V3_Cross(V3 a, V3 b) {
  return (V3){
      a.y * b.z - a.z * b.y,
      a.z * b.x - a.x * b.z,
      a.x * b.y - a.y * b.x,
  };
}

CORE_API F32 V2_Dot(V2 a, V2 b) { return a.x * b.x + a.y * b.y; }
CORE_API F32 V3_Dot(V3 a, V3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
CORE_API F32 V4_Dot(V4 a, V4 b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }

CORE_API F32 V2_LenSq(V2 v) { return v.x * v.x + v.y * v.y; }
CORE_API F32 V3_LenSq(V3 v) { return v.x * v.x + v.y * v.y + v.z * v.z; }
CORE_API F32 V4_LenSq(V4 v) { return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w; }

CORE_API F32 V2_Len(V2 v) { return Sqrt(V2_LenSq(v)); }
CORE_API F32 V3_Len(V3 v) { return Sqrt(V3_LenSq(v)); }
CORE_API F32 V4_Len(V4 v) { return Sqrt(V4_LenSq(v)); }

CORE_API F32 V2_DistSq(V2 a, V2 b) { return V2_LenSq(V2_Sub(a, b)); }
CORE_API F32 V3_DistSq(V3 a, V3 b) { return V3_LenSq(V3_Sub(a, b)); }
CORE_API F32 V4_DistSq(V4 a, V4 b) { return V4_LenSq(V4_Sub(a, b)); }

CORE_API F32 V2_Dist(V2 a, V2 b) { return Sqrt(V2_DistSq(a, b)); }
CORE_API F32 V3_Dist(V3 a, V3 b) { return Sqrt(V3_DistSq(a, b)); }
CORE_API F32 V4_Dist(V4 a, V4 b) { return Sqrt(V4_DistSq(a, b)); }
