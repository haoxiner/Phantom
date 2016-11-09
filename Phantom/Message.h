#pragma once
#include "ComponentCollection.h"
#include "Input.h"
#include "Camera.h"

namespace phtm
{
class Message
{
public:
  Message();
  ~Message();
  float deltaTimeInSeconds_;
  ComponentCollection *componentCollection_;
  Input *input_;
  Camera *camera_;
private:
};
}