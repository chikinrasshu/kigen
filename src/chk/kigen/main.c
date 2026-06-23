#include <chk/core/log.h>

#include <chk/launcher/launcher.h>

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

SDL_AppResult SDL_AppInit(Ptr* data, S32 argc, Str argv[]) {
  SDL_AppResult result = SDL_APP_FAILURE;

  if (SDL_Init(SDL_INIT_VIDEO)) {
    Launcher* launcher = SDL_malloc(sizeof(*launcher));

    if (launcher) {
      *data = launcher;

      if (Launcher_Init(launcher, "chkKigen", (V2){1280, 720}, (V2){240, 144})) {
        result = SDL_APP_CONTINUE;
      } else {
        Log_Error("Failed to initialize launcher");
      }
    } else {
      Log_Error("Failed to allocate memory for launcher");
    }
  } else {
    Log_Error("Failed to initialize SDL: %s", SDL_GetError());
  }

  return result;
}

void SDL_AppQuit(Ptr data, SDL_AppResult result) {
  (void)result;

  Launcher* launcher = data;
  if (launcher) {
    Launcher_Destroy(launcher);
    SDL_free(launcher);
  }
}

SDL_AppResult SDL_AppIterate(Ptr data) {
  SDL_AppResult result = SDL_APP_FAILURE;

  Launcher* launcher = data;
  if (launcher) {
    if (Launcher_Step(launcher)) { result = launcher->isRunning ? SDL_APP_CONTINUE : SDL_APP_SUCCESS; }
  } else {
    Log_Error("Launcher is NULL");
  }

  return result;
}

SDL_AppResult SDL_AppEvent(Ptr data, SDL_Event* event) {
  SDL_AppResult result = SDL_APP_FAILURE;

  Launcher* launcher = data;
  if (launcher) {
    if (Launcher_Event(launcher, event)) { result = launcher->isRunning ? SDL_APP_CONTINUE : SDL_APP_SUCCESS; }
  } else {
    Log_Error("Launcher is NULL");
  }

  return result;
}
