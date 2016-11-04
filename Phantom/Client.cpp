#include "Application.h"
#include <Windows.h>

int WINAPI wWinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  PWSTR pCmdLine,
  int nCmdShow)
{
  phtm::Application app;
  app.Run();
  return 0;
}