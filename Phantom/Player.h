#pragma once
#include "Entity.h"
#include "MovementComponent.h"
#include "RenderingComponent.h"

namespace phtm
{
class Player : public Entity
{
public:
  Player(
    MovementComponent *movementComponent,
    RenderingComponent *renderingComponent);
  virtual ~Player() {}
  virtual void Update(Message &message);
  float GetForwareRotation() { return forwardRotation_; }
  const DirectX::XMFLOAT3 &GetPosition() { return movementComponent_->position_; }
private:
  MovementComponent *movementComponent_;
  RenderingComponent *renderingComponent_;
  float forwardRotation_;
};
}