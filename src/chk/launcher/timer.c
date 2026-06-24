#include <chk/launcher/timer.h>

#include <chk/core/log.h>
#include <chk/core/math.h>

#include <SDL3/SDL.h>

LAUNCHER_API B8 Timer_Init(Timer* timer) {
  B8 result = false;

  if (timer) {
    result = Timer_Reset(timer);
  } else {
    Log_Error("Timer is NULL");
  }

  return result;
}

LAUNCHER_API B8 Timer_Destroy(Timer* timer) {
  B8 result = false;

  if (timer) {
    result = true;
  } else {
    Log_Error("Timer is NULL");
  }

  return result;
}

LAUNCHER_API B8 Timer_Reset(Timer* timer) {
  B8 result = false;

  if (timer) {
    timer->currentTime = 0.0f;
    timer->lastTime    = 0.0f;
    timer->deltaTime   = 0.0f;

    timer->fps    = 0.0f;
    timer->fpsMax = 0.0f;
    timer->fpsMin = 999999.0f;
    timer->fpsAvg = 0.0f;

    for (Index i = 0; i < CountOf(timer->fpsBuf); ++i) { timer->fpsBuf[i] = 0.0f; }
    timer->_fpsCur  = 0;
    timer->_fpsWrap = 1;

    result = true;
  } else {
    Log_Error("Timer is NULL");
  }

  return result;
}

LAUNCHER_API B8 Timer_Update(Timer* timer) {
  B8 result = false;

  if (timer) {
    timer->frameCount++;

    U64 ticks = SDL_GetTicks();

    timer->lastTime    = timer->currentTime;
    timer->currentTime = (F32)ticks * 0.001f;
    timer->deltaTime   = timer->currentTime - timer->lastTime;

    timer->elapsedTime += timer->deltaTime;

    timer->fps = 1.0f / timer->deltaTime;

    timer->_fpsWrap = Clamp(timer->_fpsWrap + 1, 1, CountOf(timer->fpsBuf));

    F32 fpsSum                    = 0.0f;
    timer->fpsBuf[timer->_fpsCur] = timer->fps;
    for (Index i = 0; i < timer->_fpsWrap; ++i) {
      fpsSum += timer->fpsBuf[i];
      if (timer->fpsBuf[i] > timer->fpsMax) { timer->fpsMax = timer->fpsBuf[i]; }
      if (timer->fpsBuf[i] < timer->fpsMin) { timer->fpsMin = timer->fpsBuf[i]; }
    }
    timer->fpsAvg = fpsSum / (F32)timer->_fpsWrap;

    result = true;
  } else {
    Log_Error("Timer is NULL");
  }

  return result;
}
