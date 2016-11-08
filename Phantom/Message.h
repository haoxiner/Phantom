#pragma once
#include "ComponentCollection.h"

namespace phtm
{
class Message
{
public:
  Message();
  ~Message();
  float deltaTimeInSeconds_;
  ComponentCollection *componentCollection_;
private:
};
}