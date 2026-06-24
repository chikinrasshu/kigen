#pragma once

#include <chk/launcher/api.h>

#include <chk/core/types.h>
#include <chk/core/vec.h>

typedef enum MouseBtn {
  MouseBtn_None = 0,

  MouseBtn_1,
  MouseBtn_2,
  MouseBtn_3,
  MouseBtn_4,
  MouseBtn_5,

  MouseBtn_Count,

  // Aliases

  MouseBtn_Left   = MouseBtn_1,
  MouseBtn_Right  = MouseBtn_2,
  MouseBtn_Middle = MouseBtn_3,
  MouseBtn_X1     = MouseBtn_4,
  MouseBtn_X2     = MouseBtn_5,
} MouseBtn;

typedef enum KeyboardKey {
  KeyboardKey_None,

  // Letters
  KeyboardKey_A,
  KeyboardKey_B,
  KeyboardKey_C,
  KeyboardKey_D,
  KeyboardKey_E,
  KeyboardKey_F,
  KeyboardKey_G,
  KeyboardKey_H,
  KeyboardKey_I,
  KeyboardKey_J,
  KeyboardKey_K,
  KeyboardKey_L,
  KeyboardKey_M,
  KeyboardKey_N,
  KeyboardKey_O,
  KeyboardKey_P,
  KeyboardKey_Q,
  KeyboardKey_R,
  KeyboardKey_S,
  KeyboardKey_T,
  KeyboardKey_U,
  KeyboardKey_V,
  KeyboardKey_W,
  KeyboardKey_X,
  KeyboardKey_Y,
  KeyboardKey_Z,

  // Numbers
  KeyboardKey_1,
  KeyboardKey_2,
  KeyboardKey_3,
  KeyboardKey_4,
  KeyboardKey_5,
  KeyboardKey_6,
  KeyboardKey_7,
  KeyboardKey_8,
  KeyboardKey_9,
  KeyboardKey_0,

  // Special Keys
  KeyboardKey_Return,
  KeyboardKey_Escape,
  KeyboardKey_Backspace,
  KeyboardKey_Tab,
  KeyboardKey_Space,
  KeyboardKey_Minus,
  KeyboardKey_Equals,
  KeyboardKey_LeftBracket,
  KeyboardKey_RightBracket,
  KeyboardKey_Backslash,
  KeyboardKey_Semicolon,
  KeyboardKey_Apostrophe,
  KeyboardKey_Grave,
  KeyboardKey_Comma,
  KeyboardKey_Period,
  KeyboardKey_Slash,
  KeyboardKey_CapsLock,

  // Function Keys
  KeyboardKey_F1,
  KeyboardKey_F2,
  KeyboardKey_F3,
  KeyboardKey_F4,
  KeyboardKey_F5,
  KeyboardKey_F6,
  KeyboardKey_F7,
  KeyboardKey_F8,
  KeyboardKey_F9,
  KeyboardKey_F10,
  KeyboardKey_F11,
  KeyboardKey_F12,

  // Keypad
  KeyboardKey_Insert,
  KeyboardKey_Home,
  KeyboardKey_PageUp,
  KeyboardKey_Delete,
  KeyboardKey_End,
  KeyboardKey_PageDown,
  KeyboardKey_Right,
  KeyboardKey_Left,
  KeyboardKey_Down,
  KeyboardKey_Up,

  // Modifier Keys
  KeyboardKey_LeftControl,
  KeyboardKey_LeftShift,
  KeyboardKey_LeftAlt,
  KeyboardKey_LeftGUI,
  KeyboardKey_RightControl,
  KeyboardKey_RightShift,
  KeyboardKey_RightAlt,
  KeyboardKey_RightGUI,

  KeyboardKey_Count,
} KeyboardKey;

typedef enum GamepadBtn {
  GamepadBtn_None,

  // DPad
  GamepadBtn_DPadUp,
  GamepadBtn_DPadDown,
  GamepadBtn_DPadLeft,
  GamepadBtn_DPadRight,

  // Face Buttons
  GamepadBtn_South,
  GamepadBtn_West,
  GamepadBtn_East,
  GamepadBtn_North,

  // Bumper Buttons
  GamepadBtn_LeftBumper,
  GamepadBtn_RightBumper,

  // Trigger Buttons
  GamepadBtn_LeftTrigger,
  GamepadBtn_RightTrigger,

  // Stick Clicks
  GamepadBtn_LStick,
  GamepadBtn_RStick,

  // Menu Buttons
  GamepadBtn_Back,
  GamepadBtn_Start,

  // Guide Button
  GamepadBtn_Guide,

  GamepadBtn_Count,

  // Aliases

  GamepadBtn_A = GamepadBtn_South,
  GamepadBtn_B = GamepadBtn_West,
  GamepadBtn_X = GamepadBtn_East,
  GamepadBtn_Y = GamepadBtn_North,

  GamepadBtn_Cross    = GamepadBtn_South,
  GamepadBtn_Circle   = GamepadBtn_West,
  GamepadBtn_Square   = GamepadBtn_East,
  GamepadBtn_Triangle = GamepadBtn_North,

  GamepadBtn_L1 = GamepadBtn_LeftBumper,
  GamepadBtn_R1 = GamepadBtn_RightBumper,
  GamepadBtn_L2 = GamepadBtn_LeftTrigger,
  GamepadBtn_R2 = GamepadBtn_RightTrigger,
  GamepadBtn_L3 = GamepadBtn_LStick,
  GamepadBtn_R3 = GamepadBtn_RStick,

  GamepadBtn_LB = GamepadBtn_LeftBumper,
  GamepadBtn_RB = GamepadBtn_RightBumper,
  GamepadBtn_LT = GamepadBtn_LeftTrigger,
  GamepadBtn_RT = GamepadBtn_RightTrigger,
  GamepadBtn_LS = GamepadBtn_LStick,
  GamepadBtn_RS = GamepadBtn_RStick,

  GamepadBtn_Up    = GamepadBtn_DPadUp,
  GamepadBtn_Down  = GamepadBtn_DPadDown,
  GamepadBtn_Left  = GamepadBtn_DPadLeft,
  GamepadBtn_Right = GamepadBtn_DPadRight,

  GamepadBtn_Select = GamepadBtn_Back,
  GamepadBtn_Option = GamepadBtn_Start,

  GamepadBtn_Home = GamepadBtn_Guide,
  GamepadBtn_PS   = GamepadBtn_Guide,
} GamepadBtn;

typedef enum GamepadAxis {
  GamepadAxis_None,

  // Sticks
  GamepadAxis_LStickX,
  GamepadAxis_LStickY,
  GamepadAxis_RStickX,
  GamepadAxis_RStickY,

  // Triggers
  GamepadAxis_LTrigger,
  GamepadAxis_RTrigger,

  GamepadAxis_Count,

  // Aliases

  GamepadAxis_LX = GamepadAxis_LStickX,
  GamepadAxis_LY = GamepadAxis_LStickY,
  GamepadAxis_RX = GamepadAxis_RStickX,
  GamepadAxis_RY = GamepadAxis_RStickY,

  GamepadAxis_L2 = GamepadAxis_LTrigger,
  GamepadAxis_R2 = GamepadAxis_RTrigger,

  GamepadAxis_LT = GamepadAxis_LTrigger,
  GamepadAxis_RT = GamepadAxis_RTrigger,
} GamepadAxis;

typedef struct InputBtn {
  B8 down     : 1;
  B8 pressed  : 1;
  B8 released : 1;
} InputBtn, InputKey;

typedef struct InputAxis {
  F32 value;
  F32 delta;
  F32 threshold;
} InputAxis;

typedef struct Mouse {
  B8 connected;

  V2 pos;
  V2 delta;

  InputBtn  btn[MouseBtn_Count];
  InputAxis wheel;
} Mouse;

typedef struct Keyboard {
  B8 connected;

  InputKey key[KeyboardKey_Count];
} Keyboard;

typedef struct Gamepad {
  B8 connected;

  InputBtn  btn[GamepadBtn_Count];
  InputAxis axis[GamepadAxis_Count];
} Gamepad;

typedef struct Input {
  Mouse    mouse;
  Keyboard keyboard;
  Gamepad  gamepad[4];
} Input;

LAUNCHER_API InputBtn  Input_MouseBtn(Input* input, MouseBtn btn);
LAUNCHER_API InputKey  Input_KeyboardKey(Input* input, KeyboardKey key);
LAUNCHER_API InputBtn  Input_GamepadBtn(Input* input, S32 gamepadIndex, GamepadBtn btn);
LAUNCHER_API InputAxis Input_GamepadAxis(Input* input, S32 gamepadIndex, GamepadAxis axis);

LAUNCHER_API MouseBtn    Input_MouseBtnFromRaw(S32 raw);
LAUNCHER_API KeyboardKey Input_KeyboardKeyFromRaw(S32 raw);
LAUNCHER_API GamepadBtn  Input_GamepadBtnFromRaw(S32 raw);
LAUNCHER_API GamepadAxis Input_GamepadAxisFromRaw(S32 raw);
