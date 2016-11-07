#pragma once
#include "System.h"
#include "Message.h"
#include "Entity.h"
#include <vector>

namespace phtm
{
class Engine
{
public:
  Engine();
  ~Engine();
  void Start();
  void Update(Message &message);
  void AddSystem(System *system);
private:
  std::vector<System*> systems_;
  std::vector<Entity*> entities_;
};
}