#include <chk/launcher/launcher.h>

#include <chk/core/color.h>
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
LAUNCHER_LOCAL B8 Launcher_UpdateTheme(Launcher* launcher);

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
          // Already in pixels
          S32 tmpA, tmpB;
          SDL_GetWindowPosition(impl->win, &tmpA, &tmpB);
          launcher->rect.pos.x = (F32)tmpA, launcher->rect.pos.y = (F32)tmpB;

          // Convert to pixels
          F32 pixelDensity = SDL_GetWindowPixelDensity(impl->win);
          SDL_GetWindowSize(impl->win, &tmpA, &tmpB);
          launcher->rect.size.w = (F32)tmpA * pixelDensity;
          launcher->rect.size.h = (F32)tmpB * pixelDensity;

          // Theme
          SDL_SystemTheme theme = SDL_GetSystemTheme();
          launcher->isDarkMode  = (theme == SDL_SYSTEM_THEME_DARK);
        }

        if (Launcher_UpdateVP(launcher)) {
          if (Launcher_UpdateRT(launcher)) {
            if (Launcher_UpdateTheme(launcher)) {
              if (SDL_ShowWindow(impl->win)) {
                if (Timer_Init(&launcher->timer)) {
                  launcher->isRunning = true;

                  result = true;
                } else {
                  Log_Error("Failed to initialize timer");
                }
              } else {
                Log_Error("Failed to show window: %s", SDL_GetError());
              }
            } else {
              Log_Error("Failed to update theme");
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

      Timer_Destroy(&launcher->timer);

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
      LauncherImpl* impl  = launcher->impl;
      Input*        input = &launcher->input;
      Timer*        timer = &launcher->timer;
      Palette*      pal   = &launcher->palette;

      // Pre frame
      Timer_Update(&launcher->timer);

      V2  oldMousePos  = input->mouse.pos;
      F32 pixelDensity = SDL_GetWindowPixelDensity(impl->win);
      SDL_GetGlobalMouseState(&input->mouse.pos.x, &input->mouse.pos.y);
      input->mouse.pos   = V2_Scale(V2_Sub(input->mouse.pos, launcher->rect.pos), pixelDensity);
      input->mouse.delta = V2_Sub(input->mouse.pos, oldMousePos);

      // Render frame
      B8 blit = false;
      if (impl->rt) {
        if (SDL_SetRenderTarget(impl->ctx, impl->rt)) {
          SDL_SetRenderDrawColorFloat(impl->ctx, pal->bg.r, pal->bg.g, pal->bg.b, pal->bg.a);
          SDL_RenderClear(impl->ctx);

          F32 cx = launcher->res.w * 0.5f;
          F32 cy = launcher->res.h * 0.5f;

          F32 mx = Floor(((input->mouse.pos.x - launcher->vp.pos.x) / launcher->vp.size.w) * launcher->res.w);
          F32 my = Floor(((input->mouse.pos.y - launcher->vp.pos.y) / launcher->vp.size.h) * launcher->res.h);

          if (Input_MouseBtn(input, MouseBtn_Left).down) {
            SDL_SetRenderDrawColorFloat(impl->ctx, pal->accent.r, pal->accent.g, pal->accent.b, pal->accent.a);
          } else {
            SDL_SetRenderDrawColorFloat(impl->ctx, pal->fg.r, pal->fg.g, pal->fg.b, pal->fg.a);
          }
          SDL_RenderLine(impl->ctx, cx, cy, mx, my);

          blit = true;
        }
      }

      if (SDL_SetRenderTarget(impl->ctx, NULL)) {
        SDL_SetRenderDrawColorFloat(impl->ctx, pal->desk.r, pal->desk.g, pal->desk.b, pal->desk.a);
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

      // Post frame
      for (Index i = 0; i < CountOf(input->mouse.btn); ++i) {
        input->mouse.btn[i].pressed = input->mouse.btn[i].released = false;
      }
      for (Index i = 0; i < CountOf(input->keyboard.key); ++i) {
        input->keyboard.key[i].pressed = input->keyboard.key[i].released = false;
      }
      for (Index g = 0; g < CountOf(input->gamepad); ++g) {
        for (Index i = 0; i < CountOf(input->gamepad[g].btn); ++i) {
          input->gamepad[g].btn[i].pressed = input->gamepad[g].btn[i].released = false;
        }
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
      LauncherImpl* impl  = launcher->impl;
      Input*        input = &launcher->input;

      if (rawEvent) {
        SDL_Event* event = rawEvent;

        switch (event->type) {
          case SDL_EVENT_QUIT: {
            launcher->isRunning = false;
          } break;

            // Window

          case SDL_EVENT_WINDOW_MOVED: {
            launcher->rect.pos.x = (F32)event->window.data1;
            launcher->rect.pos.y = (F32)event->window.data2;
          } break;

          case SDL_EVENT_WINDOW_RESIZED: {
            F32 winScale = SDL_GetWindowPixelDensity(impl->win);

            launcher->rect.size.x = (F32)event->window.data1 * winScale;
            launcher->rect.size.y = (F32)event->window.data2 * winScale;

            Launcher_UpdateVP(launcher);
          } break;

            // Input
          case SDL_EVENT_MOUSE_MOTION: {
            SDL_MouseMotionEvent* mme = &event->motion;

            F32 pixelDensity = SDL_GetWindowPixelDensity(impl->win);

            input->mouse.pos.x = (F32)mme->x * pixelDensity;
            input->mouse.pos.y = (F32)mme->y * pixelDensity;

            input->mouse.delta.x = (F32)mme->xrel * pixelDensity;
            input->mouse.delta.y = (F32)mme->yrel * pixelDensity;
          } break;

          case SDL_EVENT_MOUSE_WHEEL: {
            SDL_MouseWheelEvent* mwe = &event->wheel;

            input->mouse.wheel.value     = (F32)mwe->y;
            input->mouse.wheel.delta     = (F32)mwe->y;
            input->mouse.wheel.threshold = 1.0f;
          } break;

          case SDL_EVENT_MOUSE_BUTTON_DOWN:
          case SDL_EVENT_MOUSE_BUTTON_UP:   {
            SDL_MouseButtonEvent* mbe = &event->button;

            MouseBtn btn = Input_MouseBtnFromRaw(mbe->button);

            B8 wasDown = input->mouse.btn[btn].down;
            B8 isDown  = mbe->down;

            input->mouse.btn[btn].down     = isDown;
            input->mouse.btn[btn].pressed  = !wasDown && isDown;
            input->mouse.btn[btn].released = wasDown && !isDown;
          } break;

          case SDL_EVENT_KEY_DOWN:
          case SDL_EVENT_KEY_UP:   {
            SDL_KeyboardEvent* kbe = &event->key;

            KeyboardKey key = Input_KeyboardKeyFromRaw(kbe->scancode);

            B8 wasDown = input->keyboard.key[key].down;
            B8 isDown  = kbe->down;

            input->keyboard.key[key].down     = isDown;
            input->keyboard.key[key].pressed  = !wasDown && isDown;
            input->keyboard.key[key].released = wasDown && !isDown;
          } break;

            // Dark mode

          case SDL_EVENT_SYSTEM_THEME_CHANGED: {
            SDL_SystemTheme theme = SDL_GetSystemTheme();
            launcher->isDarkMode  = (theme == SDL_SYSTEM_THEME_DARK);

            Launcher_UpdateTheme(launcher);
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

LAUNCHER_LOCAL B8 Launcher_UpdateTheme(Launcher* launcher) {
  B8 result = false;

  if (launcher) {
    if (launcher->impl) {
      LauncherImpl* impl = launcher->impl;

      launcher->palette = Palette_GetDefault(launcher->isDarkMode);

      result = true;
    } else {
      Log_Error("launcher implementation is NULL");
    }
  } else {
    Log_Error("launcher is NULL");
  }

  return result;
}
