#pragma once
#include "Input.h"
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

namespace phtm
{
class InputHandler
{
public:
  InputHandler();
  bool Initialize(HINSTANCE hInstance, HWND hWnd);
  void Update();
  void Close();
  Input input_;
private:
  bool keyDown_[256];
  IDirectInputDevice8 *inputDevice_;
  IDirectInput8 *directInput_;
};
}