#include "Application.h"
#include "PhantomGame.h"

int WINAPI wWinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  PWSTR pCmdLine,
  int nCmdShow)
{
  phtm::PhantomGame game;
  phtm::Application *app = phtm::Application::GetInstance();
  app->SetGame(&game);
  app->Run();
  return 0;
}