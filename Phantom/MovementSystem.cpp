#include "MovementSystem.h"
#include "ComponentCollection.h"
#include <DirectXMath.h>
#include <algorithm>

phtm::MovementSystem::MovementSystem()
{
}

bool phtm::MovementSystem::Initialize()
{
  return true;
}

void phtm::MovementSystem::Update(Message &message)
{
  auto &movementComponent = message.componentCollection_->movementComponents_[0];
  float deltaAngle = movementComponent.rotation_ - movementComponent.instantRotation_;
  float rotateAngle = movementComponent.rotateSpeed_ * message.deltaTimeInSeconds_;
  if (std::fabsf(deltaAngle) < rotateAngle)
  {
    rotateAngle = deltaAngle;
  }
  else
  {
    if (deltaAngle < 0.0f)
    {
      rotateAngle = -rotateAngle;
    }
  }
  movementComponent.instantRotation_ += rotateAngle;
}

void phtm::MovementSystem::CleanUp()
{
}