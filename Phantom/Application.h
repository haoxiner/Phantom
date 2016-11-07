#pragma once
#include "Graphics.h"
#include <Windows.h>

namespace phtm
{
class Application
{
public:
  void Run();
protected:
  Application();
  virtual void StartGame() = 0;
  virtual void UpdateGame(float deltaTimeInSeconds) = 0;
  virtual void EndGame() = 0;
protected:
  Graphics graphics_;
  bool running_;
private:
  void Shutdown();
  bool Initialize();
  bool InitializeWindow();
private:
  LPCWSTR applicationName_;
  HINSTANCE hInstance_;
  HWND hWnd_;
};
}