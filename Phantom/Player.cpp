#include "Player.h"
#include "Message.h"
#include "Input.h"
#include <cmath>

phtm::Player::Player(
  MovementComponent *movementComponent,
  RenderingComponent *renderingComponent)
  : movementComponent_(movementComponent),
  renderingComponent_(renderingComponent)
{
  movementComponent_->rotation_ = 0.0f;
  movementComponent_->instantRotation_ = 0.0f;
  forwardRotation_ = 0.0f;
}

void phtm::Player::Update(Message &message)
{
  Input *input = message.input_;
  forwardRotation_ -= message.deltaTimeInSeconds_ * input->RightHorizontalAxis();
  forwardRotation_ = DirectX::XMScalarModAngle(forwardRotation_);
  
  if (!(input->LeftAxis() < -100.0f))
  {
    movementComponent_->rotation_ = DirectX::XMScalarModAngle(input->LeftAxis() + forwardRotation_);
    movementComponent_->rotateSpeed_ = DirectX::XMConvertToRadians(360.0f);
    movementComponent_->moveSpeed_ = 50.0f;
  }
  else
  {
    movementComponent_->rotateSpeed_ = 0.0f;
    movementComponent_->moveSpeed_ = 0.0f;
  }
}
