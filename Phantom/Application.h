#pragma once
#include "Graphics.h"
#include "Engine.h"
#include "Game.h"
#include <Windows.h>

namespace phtm
{
class Application
{
public:
  static void SetGame(Game *game);
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
  Game *game_;
  LPCWSTR applicationName_;
  HINSTANCE hInstance_;
  HWND hWnd_;
};
}