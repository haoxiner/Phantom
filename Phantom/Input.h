#pragma once

namespace phtm
{
class Input
{
public:
  Input();
  bool Quit();
  float LeftHorizontalAxis();
  float LeftVerticalAxis();
  float LeftAxis();
  bool keyDown_[256];
};
}