#include "Camera.h"
#include "Player.h"
#include "Message.h"
#include "Input.h"

phtm::Camera::Camera()
  :player_(nullptr), distance_(30.0f),
  roll_(0.0f), pitch_(0), yaw_(0.0f)
{
}

void phtm::Camera::Update(Message &message)
{
  DirectX::XMFLOAT3 focusPoint = player_->GetPosition();
  focusPoint.y += 14.0f;
  Input *input = message.input_;
  yaw_ += input->RightHorizontalAxis();
  pitch_ += input->RightVerticalAxis();
}
