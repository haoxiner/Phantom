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

  if (deltaAngle < -3.14f)
  {
    deltaAngle = 2.0f * 3.14f - deltaAngle;
  }
  else if (deltaAngle > 3.14f)
  {
    deltaAngle -= 2.0f * 3.14f;
  }
  if (std::fabsf(deltaAngle) < rotateAngle)
  {
    rotateAngle = deltaAngle;
  }
  else if (deltaAngle < 0.0f)
  {
    rotateAngle = -rotateAngle;
  }
  movementComponent.instantRotation_ += rotateAngle;

  // the rotation angle must be in [0, 2*PI)
  if (movementComponent.instantRotation_ < 0.0f)
  {
    movementComponent.instantRotation_ += 2.0f * 3.14f;
  }
  else if (movementComponent.instantRotation_ > 2.0f * 3.14f)
  {
    movementComponent.instantRotation_ -= 2.0f * 3.14f;
  }
}

void phtm::MovementSystem::CleanUp()
{
}
