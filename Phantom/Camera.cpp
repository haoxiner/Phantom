#include "Camera.h"
#include "Player.h"
#include "Message.h"
#include "Input.h"

phtm::Camera::Camera()
  :theta_(0.0f), phi_(0.45f * 3.14f), radius_(40.0f)
{
}

void phtm::Camera::Update(Message &message)
{
  DirectX::XMFLOAT3 focusPoint = message.player_->GetPosition();
  focusPoint.y += 30.0f;
  Input *input = message.input_;
  theta_ = message.player_->GetForwareRotation() + DirectX::XMConvertToRadians(-90.0f);
  phi_ += message.deltaTimeInSeconds_ * input->RightVerticalAxis();
  if (phi_ > 2.5f)
  {
    phi_ = 2.5f;
  }
  else if (phi_ > 1.5f)
  {
    radius_ = 10.0f + 30.0f * (2.5f - phi_);
  }
  else if (phi_ < 0.5f)
  {
    phi_ = 0.5f;
  }

  float sinPhiMuliplyRadius = radius_ * DirectX::XMScalarSin(phi_);
  DirectX::XMFLOAT3 position = {
    sinPhiMuliplyRadius * DirectX::XMScalarCos(theta_),
    radius_ * DirectX::XMScalarCos(phi_),
    sinPhiMuliplyRadius * DirectX::XMScalarSin(theta_)
  };

  auto simdPosition = DirectX::XMLoadFloat3(&position);
  auto simdFocusPoint = DirectX::XMLoadFloat3(&focusPoint);
  simdPosition = DirectX::XMVectorAdd(simdPosition, simdFocusPoint);
  auto up = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
  auto simdUp = DirectX::XMLoadFloat3(&up);
  DirectX::XMStoreFloat4x4(&view_, DirectX::XMMatrixLookAtLH(simdPosition, simdFocusPoint, simdUp));

}
