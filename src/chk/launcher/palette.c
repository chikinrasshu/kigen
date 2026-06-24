#include <chk/launcher/palette.h>

#include <chk/core/log.h>

LAUNCHER_API Palette Palette_GetDefault(B8 isDarkMode) {
  Palette palette = {0};

  if (isDarkMode) {
    palette.desk   = (RGBA){0.05f, 0.05f, 0.05f, 1.0f};
    palette.bg     = (RGBA){0.10f, 0.10f, 0.10f, 1.0f};
    palette.fg     = (RGBA){0.89f, 0.89f, 0.89f, 1.0f};
    palette.accent = (RGBA){0.30f, 0.56f, 0.99f, 1.0f};
  } else {
    palette.desk   = (RGBA){0.95f, 0.95f, 0.95f, 1.0f};
    palette.bg     = (RGBA){0.90f, 0.90f, 0.90f, 1.0f};
    palette.fg     = (RGBA){0.10f, 0.10f, 0.10f, 1.0f};
    palette.accent = (RGBA){0.30f, 0.56f, 0.99f, 1.0f};
  }

  return palette;
}
