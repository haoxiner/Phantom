#include "Player.h"
#include "Message.h"
#include "Input.h"
#include <cmath>

phtm::Player::Player(
  MovementComponent * movementComponent,
  RenderingComponent * renderingComponent)
  : movementComponent_(movementComponent),
  renderingComponent_(renderingComponent),
  forwardRotation_(0.0f)
{
  movementComponent_->rotation_ = 0.0f;
  movementComponent_->instantRotation_ = 3.14f * 0.5f;
  forwardRotation_ = movementComponent_->instantRotation_;
}

void phtm::Player::Update(Message &message)
{
  Input *input = message.input_;
  if (!(input->LeftAxis() < 0.0f))
  {
    movementComponent_->rotation_ = input->LeftAxis() + forwardRotation_;
    if (movementComponent_->rotation_ > 2.0f * 3.14f)
    {
      movementComponent_->rotation_ -= 2.0f * 3.14f;
    }
    movementComponent_->rotateSpeed_ = 3.141592654f * 4.0f;
  }
  else
  {
    forwardRotation_ = movementComponent_->instantRotation_;
    movementComponent_->rotateSpeed_ = 0.0f;
  }
}
