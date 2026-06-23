#include <chk/Launcher/launcher.h>

#include <chk/core/log.h>

#include <SDL3/SDL.h>

typedef struct LauncherImpl {
  SDL_Window*   win;
  SDL_Renderer* ctx;
  SDL_Texture*  rt;
} LauncherImpl;

LAUNCHER_API B8 Launcher_Init(Launcher* launcher, CStr title, V2 size, V2 res) {
  B8 result = false;

  if (launcher) {
    LauncherImpl* impl = SDL_malloc(sizeof(*launcher->impl));
    if (impl) {
      launcher->impl = impl;

      S32 winW = (S32)size.x, winH = (S32)size.y;

      SDL_WindowFlags winFlags = 0;
      winFlags |= SDL_WINDOW_HIDDEN;
      winFlags |= SDL_WINDOW_RESIZABLE;
      winFlags |= SDL_WINDOW_HIGH_PIXEL_DENSITY;
#if defined(EMSCRIPTEN)
      winFlags |= SDL_WINDOW_FILL_DOCUMENT;
#endif

      if (SDL_CreateWindowAndRenderer(title, winW, winH, winFlags, &impl->win, &impl->ctx)) {
        launcher->res = res;

        F32 pixelDensity = SDL_GetWindowPixelDensity(impl->win);

        S32 tmpA, tmpB;
        SDL_GetWindowSize(impl->win, &tmpA, &tmpB);
        launcher->rect.size.w = (F32)tmpA * pixelDensity;
        launcher->rect.size.h = (F32)tmpB * pixelDensity;
        SDL_GetWindowPosition(impl->win, &tmpA, &tmpB);
        launcher->rect.pos.x = (F32)tmpA * pixelDensity;
        launcher->rect.pos.y = (F32)tmpB * pixelDensity;

        if (SDL_ShowWindow(impl->win)) {
          launcher->isRunning = true;
          result              = true;
        }
      } else {
        Log_Error("failed to create window: %s", SDL_GetError());
      }
    } else {
      Log_Error("failed to allocate memory for launcher implementation");
    }
  } else {
    Log_Error("launcher is NULL");
  }

  return result;
}

LAUNCHER_API B8 Launcher_Destroy(Launcher* launcher) {
  B8 result = false;

  if (launcher) {
    if (launcher->impl) {
      LauncherImpl* impl = launcher->impl;

      if (impl->rt) { SDL_DestroyTexture(impl->rt), impl->rt = NULL; }
      if (impl->ctx) { SDL_DestroyRenderer(impl->ctx), impl->ctx = NULL; }
      if (impl->win) { SDL_DestroyWindow(impl->win), impl->win = NULL; }

      SDL_free(launcher->impl);
      launcher->impl = NULL;
    }

    result = true;
  } else {
    Log_Error("launcher is NULL");
  }

  return result;
}

LAUNCHER_API B8 Launcher_Step(Launcher* launcher) {
  B8 result = false;

  if (launcher) {
    if (launcher->impl) {
      LauncherImpl* impl = launcher->impl;

      if (SDL_SetRenderTarget(impl->ctx, NULL)) {
        SDL_SetRenderDrawColorFloat(impl->ctx, 0.0f, 0.1f, 0.2f, 1.0f);
        SDL_RenderClear(impl->ctx);
      }

      if (SDL_RenderPresent(impl->ctx)) {
        result = true;
      } else {
        Log_Error("failed to present frame: %s", SDL_GetError());
      }
    } else {
      Log_Error("launcher implementation is NULL");
    }
  } else {
    Log_Error("launcher is NULL");
  }

  return result;
}

LAUNCHER_API B8 Launcher_Event(Launcher* launcher, Handle rawEvent) {
  B8 result = false;

  if (launcher) {
    if (launcher->impl) {
      SDL_Event* event = rawEvent;

      switch (event->type) {
        case SDL_EVENT_QUIT: {
          launcher->isRunning = false;
        } break;
      }

      result = true;
    } else {
      Log_Error("launcher implementation is NULL");
    }
  } else {
    Log_Error("launcher is NULL");
  }

  return result;
}
