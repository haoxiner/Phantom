#include "Player.h"
#include "Message.h"
#include "Input.h"

phtm::Player::Player(
  MovementComponent * movementComponent,
  RenderingComponent * renderingComponent)
  : movementComponent_(movementComponent),
  renderingComponent_(renderingComponent)
{
  movementComponent_->rotation_ = 0.0f;
  movementComponent_->instantRotation_ = 0.0f;
  movementComponent_->rotateSpeed_ = 3.141592654f * 2.0f;
}

void phtm::Player::Update(Message &message)
{
  Input *input = message.input_;
  //movementComponent_->position_.z += 10 * message.deltaTimeInSeconds_ * input->LeftVerticalAxis();
  //movementComponent_->instantRotation_ += 10 * message.deltaTimeInSeconds_ * input->LeftHorizontalAxis();
  if (!(input->LeftAxis() < 0.0f))
  {
    movementComponent_->rotation_ = input->LeftAxis();
  }
}
