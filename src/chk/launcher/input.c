#include <chk/launcher/input.h>

#include <chk/core/log.h>

#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_mouse.h>

LAUNCHER_API InputBtn Input_MouseBtn(Input* input, MouseBtn btn) {
  InputBtn result = {0};

  if (input) {
    if (btn > MouseBtn_None && btn < MouseBtn_Count) {
      result = input->mouse.btn[btn];
    } else {
      Log_Error("Invalid mouse button: %d", btn);
    }
  } else {
    Log_Error("Input is NULL");
  }

  return result;
}

LAUNCHER_API InputKey Input_KeyboardKey(Input* input, KeyboardKey key) {
  InputKey result = {0};

  if (input) {
    if (key > KeyboardKey_None && key < KeyboardKey_Count) {
      result = input->keyboard.key[key];
    } else {
      Log_Error("Invalid keyboard key: %d", key);
    }
  } else {
    Log_Error("Input is NULL");
  }

  return result;
}

LAUNCHER_API InputBtn Input_GamepadBtn(Input* input, S32 gamepadIndex, GamepadBtn btn) {
  InputBtn result = {0};

  if (input) {
    if (gamepadIndex >= 0 && gamepadIndex < CountOf(input->gamepad)) {
      if (btn > GamepadBtn_None && btn < GamepadBtn_Count) {
        result = input->gamepad[gamepadIndex].btn[btn];
      } else {
        Log_Error("Invalid gamepad button: %d", btn);
      }
    } else {
      Log_Error("Invalid gamepad index: %d", gamepadIndex);
    }
  } else {
    Log_Error("Input is NULL");
  }

  return result;
}

LAUNCHER_API InputAxis Input_GamepadAxis(Input* input, S32 gamepadIndex, GamepadAxis axis) {
  InputAxis result = {0};

  if (input) {
    if (gamepadIndex >= 0 && gamepadIndex < CountOf(input->gamepad)) {
      if (axis > GamepadAxis_None && axis < GamepadAxis_Count) {
        result = input->gamepad[gamepadIndex].axis[axis];
      } else {
        Log_Error("Invalid gamepad axis: %d", axis);
      }
    } else {
      Log_Error("Invalid gamepad index: %d", gamepadIndex);
    }
  } else {
    Log_Error("Input is NULL");
  }

  return result;
}

LAUNCHER_API MouseBtn Input_MouseBtnFromRaw(S32 raw) {
  MouseBtn id = MouseBtn_None;

  switch (raw) {
    case SDL_BUTTON_LEFT:   id = MouseBtn_Left; break;
    case SDL_BUTTON_MIDDLE: id = MouseBtn_Middle; break;
    case SDL_BUTTON_RIGHT:  id = MouseBtn_Right; break;
    case SDL_BUTTON_X1:     id = MouseBtn_X1; break;
    case SDL_BUTTON_X2:     id = MouseBtn_X2; break;
  }

  return id;
}

LAUNCHER_API KeyboardKey Input_KeyboardKeyFromRaw(S32 raw) {
  KeyboardKey id = KeyboardKey_None;

  switch (raw) {
    // Letters
    case SDL_SCANCODE_A: id = KeyboardKey_A; break;
    case SDL_SCANCODE_B: id = KeyboardKey_B; break;
    case SDL_SCANCODE_C: id = KeyboardKey_C; break;
    case SDL_SCANCODE_D: id = KeyboardKey_D; break;
    case SDL_SCANCODE_E: id = KeyboardKey_E; break;
    case SDL_SCANCODE_F: id = KeyboardKey_F; break;
    case SDL_SCANCODE_G: id = KeyboardKey_G; break;
    case SDL_SCANCODE_H: id = KeyboardKey_H; break;
    case SDL_SCANCODE_I: id = KeyboardKey_I; break;
    case SDL_SCANCODE_J: id = KeyboardKey_J; break;
    case SDL_SCANCODE_K: id = KeyboardKey_K; break;
    case SDL_SCANCODE_L: id = KeyboardKey_L; break;
    case SDL_SCANCODE_M: id = KeyboardKey_M; break;
    case SDL_SCANCODE_N: id = KeyboardKey_N; break;
    case SDL_SCANCODE_O: id = KeyboardKey_O; break;
    case SDL_SCANCODE_P: id = KeyboardKey_P; break;
    case SDL_SCANCODE_Q: id = KeyboardKey_Q; break;
    case SDL_SCANCODE_R: id = KeyboardKey_R; break;
    case SDL_SCANCODE_S: id = KeyboardKey_S; break;
    case SDL_SCANCODE_T: id = KeyboardKey_T; break;
    case SDL_SCANCODE_U: id = KeyboardKey_U; break;
    case SDL_SCANCODE_V: id = KeyboardKey_V; break;
    case SDL_SCANCODE_W: id = KeyboardKey_W; break;
    case SDL_SCANCODE_X: id = KeyboardKey_X; break;
    case SDL_SCANCODE_Y: id = KeyboardKey_Y; break;
    case SDL_SCANCODE_Z: id = KeyboardKey_Z; break;

    // Numbers
    case SDL_SCANCODE_1: id = KeyboardKey_1; break;
    case SDL_SCANCODE_2: id = KeyboardKey_2; break;
    case SDL_SCANCODE_3: id = KeyboardKey_3; break;
    case SDL_SCANCODE_4: id = KeyboardKey_4; break;
    case SDL_SCANCODE_5: id = KeyboardKey_5; break;
    case SDL_SCANCODE_6: id = KeyboardKey_6; break;
    case SDL_SCANCODE_7: id = KeyboardKey_7; break;
    case SDL_SCANCODE_8: id = KeyboardKey_8; break;
    case SDL_SCANCODE_9: id = KeyboardKey_9; break;
    case SDL_SCANCODE_0: id = KeyboardKey_0; break;

    // Special Keys
    case SDL_SCANCODE_RETURN:       id = KeyboardKey_Return; break;
    case SDL_SCANCODE_ESCAPE:       id = KeyboardKey_Escape; break;
    case SDL_SCANCODE_BACKSPACE:    id = KeyboardKey_Backspace; break;
    case SDL_SCANCODE_TAB:          id = KeyboardKey_Tab; break;
    case SDL_SCANCODE_SPACE:        id = KeyboardKey_Space; break;
    case SDL_SCANCODE_MINUS:        id = KeyboardKey_Minus; break;
    case SDL_SCANCODE_EQUALS:       id = KeyboardKey_Equals; break;
    case SDL_SCANCODE_LEFTBRACKET:  id = KeyboardKey_LeftBracket; break;
    case SDL_SCANCODE_RIGHTBRACKET: id = KeyboardKey_RightBracket; break;
    case SDL_SCANCODE_BACKSLASH:    id = KeyboardKey_Backslash; break;
    case SDL_SCANCODE_SEMICOLON:    id = KeyboardKey_Semicolon; break;
    case SDL_SCANCODE_APOSTROPHE:   id = KeyboardKey_Apostrophe; break;
    case SDL_SCANCODE_GRAVE:        id = KeyboardKey_Grave; break;
    case SDL_SCANCODE_COMMA:        id = KeyboardKey_Comma; break;
    case SDL_SCANCODE_PERIOD:       id = KeyboardKey_Period; break;
    case SDL_SCANCODE_SLASH:        id = KeyboardKey_Slash; break;
    case SDL_SCANCODE_CAPSLOCK:     id = KeyboardKey_CapsLock; break;

    // Function Keys
    case SDL_SCANCODE_F1:  id = KeyboardKey_F1; break;
    case SDL_SCANCODE_F2:  id = KeyboardKey_F2; break;
    case SDL_SCANCODE_F3:  id = KeyboardKey_F3; break;
    case SDL_SCANCODE_F4:  id = KeyboardKey_F4; break;
    case SDL_SCANCODE_F5:  id = KeyboardKey_F5; break;
    case SDL_SCANCODE_F6:  id = KeyboardKey_F6; break;
    case SDL_SCANCODE_F7:  id = KeyboardKey_F7; break;
    case SDL_SCANCODE_F8:  id = KeyboardKey_F8; break;
    case SDL_SCANCODE_F9:  id = KeyboardKey_F9; break;
    case SDL_SCANCODE_F10: id = KeyboardKey_F10; break;
    case SDL_SCANCODE_F11: id = KeyboardKey_F11; break;
    case SDL_SCANCODE_F12: id = KeyboardKey_F12; break;

    // Keypad
    case SDL_SCANCODE_INSERT:   id = KeyboardKey_Insert; break;
    case SDL_SCANCODE_HOME:     id = KeyboardKey_Home; break;
    case SDL_SCANCODE_PAGEUP:   id = KeyboardKey_PageUp; break;
    case SDL_SCANCODE_DELETE:   id = KeyboardKey_Delete; break;
    case SDL_SCANCODE_END:      id = KeyboardKey_End; break;
    case SDL_SCANCODE_PAGEDOWN: id = KeyboardKey_PageDown; break;
    case SDL_SCANCODE_RIGHT:    id = KeyboardKey_Right; break;
    case SDL_SCANCODE_LEFT:     id = KeyboardKey_Left; break;
    case SDL_SCANCODE_DOWN:     id = KeyboardKey_Down; break;
    case SDL_SCANCODE_UP:       id = KeyboardKey_Up; break;

    // Modifier Keys
    case SDL_SCANCODE_LCTRL:  id = KeyboardKey_LeftControl; break;
    case SDL_SCANCODE_LSHIFT: id = KeyboardKey_LeftShift; break;
    case SDL_SCANCODE_LALT:   id = KeyboardKey_LeftAlt; break;
    case SDL_SCANCODE_LGUI:   id = KeyboardKey_LeftGUI; break;
    case SDL_SCANCODE_RCTRL:  id = KeyboardKey_RightControl; break;
    case SDL_SCANCODE_RSHIFT: id = KeyboardKey_RightShift; break;
    case SDL_SCANCODE_RALT:   id = KeyboardKey_RightAlt; break;
    case SDL_SCANCODE_RGUI:   id = KeyboardKey_RightGUI; break;
  }

  return id;
}

LAUNCHER_API GamepadBtn Input_GamepadBtnFromRaw(S32 raw) {
  GamepadBtn id = GamepadBtn_None;

  switch (raw) {
    // Face Buttons
    case SDL_GAMEPAD_BUTTON_SOUTH: id = GamepadBtn_A; break;
    case SDL_GAMEPAD_BUTTON_EAST:  id = GamepadBtn_B; break;
    case SDL_GAMEPAD_BUTTON_WEST:  id = GamepadBtn_X; break;
    case SDL_GAMEPAD_BUTTON_NORTH: id = GamepadBtn_Y; break;

    // Shoulder Buttons
    case SDL_GAMEPAD_BUTTON_LEFT_SHOULDER:  id = GamepadBtn_LB; break;
    case SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER: id = GamepadBtn_RB; break;

    // Menu Buttons
    case SDL_GAMEPAD_BUTTON_BACK:  id = GamepadBtn_Back; break;
    case SDL_GAMEPAD_BUTTON_START: id = GamepadBtn_Start; break;

    // Stick Clicks
    case SDL_GAMEPAD_BUTTON_LEFT_STICK:  id = GamepadBtn_LStick; break;
    case SDL_GAMEPAD_BUTTON_RIGHT_STICK: id = GamepadBtn_RStick; break;

    // Guide Button
    case SDL_GAMEPAD_BUTTON_GUIDE: id = GamepadBtn_Guide; break;
  }

  return id;
}

LAUNCHER_API GamepadAxis Input_GamepadAxisFromRaw(S32 raw) {
  GamepadAxis id = GamepadAxis_None;

  switch (raw) {
    // Left Stick
    case SDL_GAMEPAD_AXIS_LEFTX: id = GamepadAxis_LStickX; break;
    case SDL_GAMEPAD_AXIS_LEFTY: id = GamepadAxis_LStickY; break;

    // Right Stick
    case SDL_GAMEPAD_AXIS_RIGHTX: id = GamepadAxis_RStickX; break;
    case SDL_GAMEPAD_AXIS_RIGHTY: id = GamepadAxis_RStickY; break;

    // Triggers
    case SDL_GAMEPAD_AXIS_LEFT_TRIGGER:  id = GamepadAxis_LTrigger; break;
    case SDL_GAMEPAD_AXIS_RIGHT_TRIGGER: id = GamepadAxis_RTrigger; break;
  }

  return id;
}
