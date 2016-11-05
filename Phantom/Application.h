#pragma once
#include "Graphics.h"
#include <Windows.h>

namespace phtm
{
class Application
{
public:
  static Application *GetInstance();
  void Run();
  LRESULT CALLBACK HandleMessage(HWND, UINT, WPARAM, LPARAM);
private:
  Application();
  void Shutdown();
  bool Initialize();
  bool InitializeWindow();
private:
  static Application *applicationInstance_;
  Graphics graphics_;
  LPCWSTR applicationName_;
  HINSTANCE hInstance_;
  HWND hWnd_;
};
}