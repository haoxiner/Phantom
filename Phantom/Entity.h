#pragma once
#include "Message.h"

namespace phtm
{
class Entity
{
public:
  Entity() {}
  virtual ~Entity() = 0;
  virtual void Update(Message &message) = 0;
private:

};
}