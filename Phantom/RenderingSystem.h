#pragma once
#include "System.h"

namespace phtm
{
class RenderingSystem : public System
{
public:
  RenderingSystem() {}
  virtual ~RenderingSystem() {}
  virtual void Update(Message &message);
private:

};
}