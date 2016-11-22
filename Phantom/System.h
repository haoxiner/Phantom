#pragma once
#include "Message.h"

namespace phtm
{
class System
{
public:
  System() {}
  virtual ~System() {};
  virtual void Update(Message &message) = 0;
  virtual void CleanUp() = 0;
private:

};
}