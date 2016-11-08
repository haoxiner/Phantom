#include "Engine.h"

void phtm::Engine::Start()
{
  for (auto system : systems_)
  {
    system->Initialize();
  }
}

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

void phtm::Engine::Shutdown()
{
  for (auto system : systems_)
  {
    system->CleanUp();
  }
}
