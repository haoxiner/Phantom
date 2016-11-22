#pragma once
#include "Entity.h"
#include "MovementComponent.h"
#include "RenderingComponent.h"

namespace phtm
{
class Player : public Entity
{
public:
  Player();
  virtual ~Player() {}
  virtual void Update(Message &message);
  void Initialize(
    MovementComponent *movementComponent,
    RenderingComponent *renderingComponent);
  float GetForwardRotation() { return forwardRotation_; }
  const DirectX::XMFLOAT3 &GetPosition() { return movementComponent_->position_; }
private:
  MovementComponent *movementComponent_;
  RenderingComponent *renderingComponent_;
  float forwardRotation_;
};
}