#include "MovementSystem.h"
#include "ComponentCollection.h"

phtm::MovementSystem::MovementSystem()
{
}

bool phtm::MovementSystem::Initialize()
{
  return false;
}

void phtm::MovementSystem::Update(Message &message)
{
  auto &movementComponent = message.componentCollection_->movementComponents_[0];

}

void phtm::MovementSystem::CleanUp()
{
}
