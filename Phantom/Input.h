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
  float RightHorizontalAxis();
  float RightVerticalAxis();
  bool keyDown_[256];
};
}