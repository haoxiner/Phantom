#pragma once

namespace phtm
{
class Input
{
public:
  Input();
  bool Quit();
  float LeftHorizontalAxisX();
  float LeftHorizontalAxisY();
  bool keyDown_[256];
};
}