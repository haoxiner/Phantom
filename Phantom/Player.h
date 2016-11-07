#pragma once
#include "Entity.h"

namespace phtm
{
class Player : public Entity
{
public:
  Player() {}
  virtual ~Player() {}
  virtual void Update(Message &message);
private:

};
}