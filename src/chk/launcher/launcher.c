#include <chk/Launcher/launcher.h>

#include <chk/core/log.h>
#include <chk/core/math.h>

#include <SDL3/SDL.h>

typedef struct LauncherImpl {
  SDL_Window*   win;
  SDL_Renderer* ctx;
  SDL_Texture*  rt;
} LauncherImpl;

LAUNCHER_LOCAL B8 Launcher_UpdateVP(Launcher* launcher);
LAUNCHER_LOCAL B8 Launcher_UpdateRT(Launcher* launcher);

LAUNCHER_API B8 Launcher_Init(Launcher* launcher, CStr title, V2 size, V2 res) {
  B8 result = false;

  if (launcher) {
    LauncherImpl* impl = SDL_calloc(1, sizeof(*launcher->impl));
    if (impl) {
      launcher->impl = impl;
      launcher->res  = res;

      S32 winW = (S32)size.x, winH = (S32)size.y;

      SDL_WindowFlags winFlags = 0;
      winFlags |= SDL_WINDOW_HIDDEN;
      winFlags |= SDL_WINDOW_RESIZABLE;
      winFlags |= SDL_WINDOW_HIGH_PIXEL_DENSITY;
#if defined(EMSCRIPTEN)
      winFlags |= SDL_WINDOW_FILL_DOCUMENT;
#endif

      if (SDL_CreateWindowAndRenderer(title, winW, winH, winFlags, &impl->win, &impl->ctx)) {
        CStr rendererName = SDL_GetRendererName(impl->ctx);
        if (rendererName) { Log_Info("Renderer: %s", rendererName); }

        if (SDL_SetRenderVSync(impl->ctx, SDL_RENDERER_VSYNC_ADAPTIVE)) {
          Log_Info("VSync: enabled (adaptive)");
        } else {
          if (SDL_SetRenderVSync(impl->ctx, 1)) {
            Log_Info("VSync: enabled (standard)");
          } else {
            Log_Warn("VSync: disabled (%s)", SDL_GetError());
          }
        }

        {
          F32 pixelDensity = SDL_GetWindowPixelDensity(impl->win);

          S32 tmpA, tmpB;
          SDL_GetWindowPosition(impl->win, &tmpA, &tmpB);
          launcher->rect.pos.x = (F32)tmpA * pixelDensity;
          launcher->rect.pos.y = (F32)tmpB * pixelDensity;
          SDL_GetWindowSize(impl->win, &tmpA, &tmpB);
          launcher->rect.size.w = (F32)tmpA * pixelDensity;
          launcher->rect.size.h = (F32)tmpB * pixelDensity;
        }

        if (Launcher_UpdateVP(launcher)) {
          if (Launcher_UpdateRT(launcher)) {
            if (SDL_ShowWindow(impl->win)) {
              launcher->isRunning = true;

              result = true;
            } else {
              Log_Error("Failed to show window: %s", SDL_GetError());
            }
          } else {
            Log_Error("Failed to update render target");
          }
        } else {
          Log_Error("Failed to update viewport");
        }
      } else {
        Log_Error("Failed to create window: %s", SDL_GetError());
      }
    } else {
      Log_Error("Failed to allocate memory for launcher implementation");
    }
  } else {
    Log_Error("Launcher is NULL");
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

      B8 blit = false;
      if (impl->rt) {
        if (SDL_SetRenderTarget(impl->ctx, impl->rt)) {
          SDL_SetRenderDrawColorFloat(impl->ctx, 0.1f, 0.2f, 0.3f, 1.0f);
          SDL_RenderClear(impl->ctx);

          blit = true;
        }
      }

      if (SDL_SetRenderTarget(impl->ctx, NULL)) {
        SDL_SetRenderDrawColorFloat(impl->ctx, 0.0f, 0.1f, 0.2f, 1.0f);
        SDL_RenderClear(impl->ctx);

        if (blit) {
          SDL_FRect dst = {launcher->vp.pos.x, launcher->vp.pos.y, launcher->vp.size.w, launcher->vp.size.h};
          SDL_RenderTexture(impl->ctx, impl->rt, NULL, &dst);
        }
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
      LauncherImpl* impl = launcher->impl;

      if (rawEvent) {
        SDL_Event* event = rawEvent;

        switch (event->type) {
          case SDL_EVENT_QUIT: {
            launcher->isRunning = false;
          } break;

            // Window

          case SDL_EVENT_WINDOW_RESIZED: {
            F32 winScale = SDL_GetWindowPixelDensity(impl->win);

            launcher->rect.size.x = (F32)event->window.data1 * winScale;
            launcher->rect.size.y = (F32)event->window.data2 * winScale;

            Launcher_UpdateVP(launcher);
          } break;
        }

        result = true;
      } else {
        Log_Error("event is NULL");
      }
    } else {
      Log_Error("launcher implementation is NULL");
    }
  } else {
    Log_Error("launcher is NULL");
  }

  return result;
}

LAUNCHER_LOCAL B8 Launcher_UpdateVP(Launcher* launcher) {
  B8 result = false;

  if (launcher) {
    if (launcher->impl) {
      LauncherImpl* impl = launcher->impl;

      F32 pixelDensity = SDL_GetWindowPixelDensity(impl->win);

      V2  aspect = V2_Div(launcher->rect.size, launcher->res);
      F32 scale  = Min(aspect.x, aspect.y);

      if (scale > 1.0f) { scale = Floor(scale); }

      launcher->vp.size = V2_Scale(launcher->res, scale);
      launcher->vp.pos  = V2_Scale(V2_Sub(launcher->rect.size, launcher->vp.size), 0.5f);

      Log_Info("ws = %f, %f", launcher->rect.size.x, launcher->rect.size.y);
      Log_Info("rs = %f, %f", launcher->res.x, launcher->res.y);
      Log_Info("vp = %f, %f, %f, %f", launcher->vp.pos.x, launcher->vp.pos.y, launcher->vp.size.w, launcher->vp.size.h);

      result = true;
    } else {
      Log_Error("launcher implementation is NULL");
    }
  } else {
    Log_Error("launcher is NULL");
  }

  return result;
}

LAUNCHER_LOCAL B8 Launcher_UpdateRT(Launcher* launcher) {
  B8 result = false;

  if (launcher) {
    if (launcher->impl) {
      LauncherImpl* impl = launcher->impl;

      B8 recreate = false;
      if (impl->rt) {
        F32 rw, rh;
        SDL_GetTextureSize(impl->rt, &rw, &rh);

        // Check if the rt size changed
        if (rw != launcher->res.w || rh != launcher->res.h) {
          SDL_DestroyTexture(impl->rt), impl->rt = NULL;

          recreate = true;
        }
      } else {
        recreate = true;
      }

      if (recreate) {
        SDL_PixelFormat   fmt = SDL_PIXELFORMAT_ABGR8888;
        SDL_TextureAccess acc = SDL_TEXTUREACCESS_TARGET;

        impl->rt = SDL_CreateTexture(impl->ctx, fmt, acc, (S32)launcher->res.w, (S32)launcher->res.h);
        if (impl->rt) {
          SDL_SetTextureBlendMode(impl->rt, SDL_BLENDMODE_BLEND);
          SDL_SetTextureScaleMode(impl->rt, SDL_SCALEMODE_NEAREST);

          Log_Info("Resized render target to %.2f, %.2f", launcher->res.w, launcher->res.h);

          result = true;
        } else {
          Log_Error("Failed to create render target: %s", SDL_GetError());
        }
      } else {
        result = true;
      }
    } else {
      Log_Error("launcher implementation is NULL");
    }
  } else {
    Log_Error("launcher is NULL");
  }

  return result;
}
