#pragma once
#include "System.h"
#include "Message.h"
#include "Entity.h"
#include "Graphics.h"
#include <vector>

namespace phtm
{
class Engine
{
public:
  void Start();
  void Update(Message &message);
  void AddSystem(System *system);
  void Shutdown();
private:
  std::vector<System*> systems_;
  std::vector<Entity*> entities_;
};
}