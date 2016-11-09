#pragma once
#include <dinput.h>

namespace phtm
{
class Input
{
public:
  Input();
  bool Quit();
  float LeftHorizontalAxisX();
  float LeftHorizontalAxisY();
  bool Initialize(HINSTANCE hInstance, HWND hWnd);
  void Update();
  void Close();
private:
  bool keyDown_[256];
  IDirectInputDevice8 *inputDevice_;
  IDirectInput8 *directInput_;
};
}