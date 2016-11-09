#pragma once
#include "Graphics.h"
#include "Input.h"
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
  Input input_;
  bool running_;
  int screenWidth_;
  int screenHeight_;
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