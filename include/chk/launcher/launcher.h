#pragma once

#include <chk/launcher/api.h>

#include <chk/core/types.h>
#include <chk/core/vec.h>

typedef struct LauncherImpl LauncherImpl;

typedef struct Launcher {
  B8 isRunning    : 1;
  B8 isVisible    : 1;
  B8 isFullscreen : 1;
  B8 isFocused    : 1;
  B8 isHovered    : 1;
  B8 isMinimized  : 1;
  B8 isMaximized  : 1;

  V4 rect;
  V4 vp;
  V2 res;

  LauncherImpl* impl;
} Launcher;

LAUNCHER_API B8 Launcher_Init(Launcher* launcher, CStr title, V2 size, V2 res);
LAUNCHER_API B8 Launcher_Destroy(Launcher* launcher);

LAUNCHER_API B8 Launcher_Step(Launcher* launcher);
LAUNCHER_API B8 Launcher_Event(Launcher* launcher, Handle event);
