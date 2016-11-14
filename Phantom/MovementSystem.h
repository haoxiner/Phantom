#pragma once
#include "System.h"
#include "Message.h"

namespace phtm
{
class MovementSystem : public System
{
public:
  MovementSystem();
  virtual ~MovementSystem() {};
  virtual bool Initialize();
  virtual void Update(Message &message);
  virtual void CleanUp();
private:

};
}