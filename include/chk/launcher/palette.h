#pragma once

#include <chk/launcher/api.h>

#include <chk/core/color.h>
#include <chk/core/types.h>

typedef struct Palette {
  RGBA desk;
  RGBA bg;
  RGBA fg;
  RGBA accent;
} Palette;

LAUNCHER_API Palette Palette_GetDefault(B8 isDarkMode);
