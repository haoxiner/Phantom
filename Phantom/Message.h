#pragma once
#include "ComponentCollection.h"
#include "Input.h"

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
private:
};
}