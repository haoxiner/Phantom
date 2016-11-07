#include "Game.h"

int WINAPI wWinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  PWSTR pCmdLine,
  int nCmdShow)
{
  phtm::Game game;
  game.Run();
  return 0;
}