#pragma once
#include <Windows.h>

namespace phtm
{
class Display
{
public:
  bool Initialize();
  bool IsRunning();
  void Update();
private:
  LPCWSTR applicationName_;
  HINSTANCE hInstance_;
  HWND hWnd_;
};
}