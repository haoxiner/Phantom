#include "Input.h"
#include <dinput.h>
#include <DirectXMath.h>

phtm::Input::Input()
{
}

bool phtm::Input::Quit()
{
  return keyDown_[DIK_Q];
}

float phtm::Input::LeftHorizontalAxis()
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

float phtm::Input::LeftVerticalAxis()
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

#define M_PI        3.14159265358979323846
#define M_PI_2        1.57079632679489661923
#define M_PI_4        0.78539816339744830962
#define M_1_PI        0.31830988618379067154
#define M_2_PI        0.63661977236758134308
#define M_2_SQRTPI    1.12837916709551257390
static float table[3][3] =
{
  M_PI*0.25f, M_PI*0.0f, M_PI*-0.25f,
  M_PI*0.50f,   -500.0f, M_PI*-0.50f,
  M_PI*0.75f, M_PI*1.0f, M_PI*-0.75f
};
float phtm::Input::LeftAxis()
{
  int horizontal = 1, vertical = 1;
  if (keyDown_[DIK_D])
  {
    ++horizontal;
  }
  if (keyDown_[DIK_A])
  {
    --horizontal;
  }
  if (keyDown_[DIK_W])
  {
    --vertical;
  }
  if (keyDown_[DIK_S])
  {
    ++vertical;
  }
  return table[vertical][horizontal];
}

float phtm::Input::RightHorizontalAxis()
{
  float value = 0.0f;
  if (keyDown_[DIK_LEFT])
  {
    value -= 1.0f;
  }
  if (keyDown_[DIK_RIGHT])
  {
    value += 1.0f;
  }
  return value;
}

float phtm::Input::RightVerticalAxis()
{
  float value = 0.0f;
  if (keyDown_[DIK_DOWN])
  {
    value -= 1.0f;
  }
  if (keyDown_[DIK_UP])
  {
    value += 1.0f;
  }
  return value;
}
