#pragma once
#include "Display.h"
#include "Graphics.h"

namespace phtm
{
class Application
{
public:
  Application();
  void Run();
private:
  bool Initialize();
  void Close();
private:
  Display *display_;
  Graphics *graphics_;
  bool running_;
};
}