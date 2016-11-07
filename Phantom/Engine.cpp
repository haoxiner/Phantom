#include "Engine.h"

void phtm::Engine::Update(Message &message)
{
  for (auto entity : entities_)
  {
    entity->Update(message);
  }
  for (auto system : systems_)
  {
    system->Update(message);
  }
}

void phtm::Engine::AddSystem(System *system)
{
  systems_.push_back(system);
}
