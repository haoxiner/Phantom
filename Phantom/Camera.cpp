#include "Camera.h"
#include "Player.h"

phtm::Camera::Camera()
  :player_(nullptr), distance_(30.0f)
{
}

void phtm::Camera::Update(Message &message)
{
  DirectX::XMFLOAT3 focusPoint = player_->GetPosition();
  focusPoint.y += 14.0f;
}
