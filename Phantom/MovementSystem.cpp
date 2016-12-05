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
  for (auto &movementComponent : message.componentCollection_->movementComponents_)
  {
    if (!movementComponent.IsActive())
    {
      continue;
    }
    float deltaAngle = DirectX::XMScalarModAngle(movementComponent.rotation_ - movementComponent.instantRotation_);
    float rotateAngle = movementComponent.rotateSpeed_ * message.deltaTimeInSeconds_;
    if (std::fabsf(deltaAngle) < std::fabsf(rotateAngle))
    {
      rotateAngle = deltaAngle;
    }
    else if (deltaAngle < 0.0f)
    {
      rotateAngle = -rotateAngle;
    }
    movementComponent.instantRotation_ += rotateAngle;
    movementComponent.instantRotation_ = DirectX::XMScalarModAngle(movementComponent.instantRotation_);
    if (std::fabsf(rotateAngle) < 0.01f)
    {
      DirectX::XMFLOAT4 direction(0.0f, -1.0f, 0.0f, 1.0f);
      auto simdDirection = DirectX::XMLoadFloat4(&direction);
      auto simdRotationMat = DirectX::XMMatrixRotationZ(-movementComponent.instantRotation_);
      simdDirection = DirectX::XMVector4Transform(simdDirection, simdRotationMat);
      simdDirection = DirectX::XMVector3Normalize(simdDirection);
      simdDirection = DirectX::XMVectorScale(simdDirection, movementComponent.moveSpeed_ * message.deltaTimeInSeconds_);
      auto simdPosition = DirectX::XMLoadFloat3(&movementComponent.position_);
      simdPosition = DirectX::XMVectorAdd(simdPosition, simdDirection);
      DirectX::XMStoreFloat3(&movementComponent.position_, simdPosition);
    }
  }
}

void phtm::MovementSystem::CleanUp()
{
}
