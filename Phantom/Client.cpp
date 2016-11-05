#include "Application.h"
#include <Windows.h>

int WINAPI wWinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  PWSTR pCmdLine,
  int nCmdShow)
{
  phtm::Application *app = phtm::Application::GetInstance();
  app->Run();
  return 0;
}