#pragma once
#include "Graphics.h"

namespace phtm
{
class Application
{
public:
  static Application *GetInstance();
  void Run();
private:
  Application();
  void Shutdown();
  bool Initialize();
  bool InitializeWindow();
  LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
private:
  static Application *applicationInstance_;
  Graphics graphics_;
  LPCWSTR applicationName_;
  HINSTANCE hInstance_;
  HWND hWnd_;
};
}