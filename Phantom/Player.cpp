#include "Player.h"
#include "Message.h"
#include "Input.h"

phtm::Player::Player(
  MovementComponent * movementComponent,
  RenderingComponent * renderingComponent)
  : movementComponent_(movementComponent),
  renderingComponent_(renderingComponent)
{
}

void phtm::Player::Update(Message &message)
{
  Input *input = message.input_;
  movementComponent_->position_.z += 10 * message.deltaTimeInSeconds_ * input->LeftHorizontalAxisY();
  movementComponent_->instantRotation_ += 10 * message.deltaTimeInSeconds_ * input->LeftHorizontalAxisX();
}
