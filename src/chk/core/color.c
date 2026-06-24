#include <chk/core/color.h>

#include <chk/core/math.h>

CORE_API RGBA RGBA_FromHSLA(HSLA hsla) {
  hsla.h = hsla.h - Floor(hsla.h);

  F32 saturation = Clamp(hsla.s, 0.0f, 1.0f);
  F32 lightness  = Clamp(hsla.l, 0.0f, 1.0f);
  F32 alpha      = Clamp(hsla.a, 0.0f, 1.0f);

  F32 chroma = (1.0f - Abs(2.0f * lightness - 1.0f)) * saturation;
  F32 hue    = hsla.h * 6.0f;
  F32 x      = chroma * (1.0f - Abs((hue - 2.0f * Floor(hue / 2.0f)) - 1.0f));
  F32 match  = lightness - chroma / 2.0f;

  RGBA rgba = {0};

  if (hue < 1.0f) {
    rgba.r = chroma;
    rgba.g = x;
  } else if (hue < 2.0f) {
    rgba.r = x;
    rgba.g = chroma;
  } else if (hue < 3.0f) {
    rgba.g = chroma;
    rgba.b = x;
  } else if (hue < 4.0f) {
    rgba.g = x;
    rgba.b = chroma;
  } else if (hue < 5.0f) {
    rgba.r = x;
    rgba.b = chroma;
  } else {
    rgba.r = chroma;
    rgba.b = x;
  }

  rgba.r += match;
  rgba.g += match;
  rgba.b += match;
  rgba.a = alpha;

  return rgba;
}

CORE_API HSLA HSLA_FromRGBA(RGBA rgba) {
  F32 red   = Clamp(rgba.r, 0.0f, 1.0f);
  F32 green = Clamp(rgba.g, 0.0f, 1.0f);
  F32 blue  = Clamp(rgba.b, 0.0f, 1.0f);
  F32 alpha = Clamp(rgba.a, 0.0f, 1.0f);

  F32 max    = Max(Max(red, green), blue);
  F32 min    = Min(Min(red, green), blue);
  F32 chroma = max - min;

  HSLA hsla = {0};
  hsla.l    = (max + min) * 0.5f;
  hsla.a    = alpha;

  if (chroma == 0.0f) { return hsla; }

  hsla.s = chroma / (1.0f - Abs(2.0f * hsla.l - 1.0f));

  if (max == red) {
    hsla.h = (green - blue) / chroma;
    if (green < blue) { hsla.h += 6.0f; }
  } else if (max == green) {
    hsla.h = ((blue - red) / chroma) + 2.0f;
  } else {
    hsla.h = ((red - green) / chroma) + 4.0f;
  }

  hsla.h /= 6.0f;

  return hsla;
}

CORE_API RGBA RGBA_FromHex(U32 hex) {
  RGBA rgba = {0};

  // Colors are packed as 0xAABBGGRR
  rgba.r = ((hex >> 0) & 0xFF) / 255.0f;
  rgba.g = ((hex >> 8) & 0xFF) / 255.0f;
  rgba.b = ((hex >> 16) & 0xFF) / 255.0f;
  rgba.a = ((hex >> 24) & 0xFF) / 255.0f;

  return rgba;
}

CORE_API U32 RGBA_ToHex(RGBA rgba) {
  U32 hex = 0;

  // Colors are packed as 0xAABBGGRR
  hex |= ((U32)(Clamp(rgba.r, 0.0f, 1.0f) * 255.0f) & 0xFF) << 0;
  hex |= ((U32)(Clamp(rgba.g, 0.0f, 1.0f) * 255.0f) & 0xFF) << 8;
  hex |= ((U32)(Clamp(rgba.b, 0.0f, 1.0f) * 255.0f) & 0xFF) << 16;
  hex |= ((U32)(Clamp(rgba.a, 0.0f, 1.0f) * 255.0f) & 0xFF) << 24;

  return hex;
}

CORE_API RGBA RGBA_Lerp(RGBA a, RGBA b, F32 t) {
  return RGBA_FromHSLA(HSLA_Lerp(HSLA_FromRGBA(a), HSLA_FromRGBA(b), t));
}

CORE_API HSLA HSLA_Lerp(HSLA a, HSLA b, F32 t) {
  t = Clamp(t, 0.0f, 1.0f);

  F32 hueDelta = b.h - a.h;

  if (hueDelta > 0.5f) {
    hueDelta -= 1.0f;
  } else if (hueDelta < -0.5f) {
    hueDelta += 1.0f;
  }

  HSLA hsla = {0};
  hsla.h    = a.h + hueDelta * t;
  hsla.h    = hsla.h - Floor(hsla.h);
  hsla.s    = Lerp(a.s, b.s, t);
  hsla.l    = Lerp(a.l, b.l, t);
  hsla.a    = Lerp(a.a, b.a, t);

  return hsla;
}
