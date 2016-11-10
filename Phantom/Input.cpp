#include "Input.h"
#include <dinput.h>

phtm::Input::Input()
{
}

bool phtm::Input::Quit()
{
  return keyDown_[DIK_Q];
}

float phtm::Input::LeftHorizontalAxisX()
{
  float value = 0.0f;
  if (keyDown_[DIK_D])
  {
    value += 1.0f;
  }
  if (keyDown_[DIK_A])
  {
    value -= 1.0f;
  }
  return value;
}

float phtm::Input::LeftHorizontalAxisY()
{
  float value = 0.0f;
  if (keyDown_[DIK_W])
  {
    value += 1.0f;
  }
  if (keyDown_[DIK_S])
  {
    value -= 1.0f;
  }
  return value;
}