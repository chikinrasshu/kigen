#pragma once

#include <chk/launcher/api.h>

#include <chk/core/types.h>

typedef struct Timer {
  F32 currentTime, lastTime, deltaTime;
  F32 elapsedTime;

  F32 fps, fpsMax, fpsMin, fpsAvg;
  F32 fpsBuf[64];
  U32 _fpsCur, _fpsWrap;

  U64 frameCount;
} Timer;

LAUNCHER_API B8 Timer_Init(Timer* timer);
LAUNCHER_API B8 Timer_Destroy(Timer* timer);

LAUNCHER_API B8 Timer_Reset(Timer* timer);
LAUNCHER_API B8 Timer_Update(Timer* timer);
