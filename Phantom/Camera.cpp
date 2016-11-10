#include "Camera.h"

phtm::Camera::Camera()
{
  auto scale = DirectX::XMMatrixScaling(0.1f, 0.1f, 0.1f);
  auto rotate = DirectX::XMMatrixRotationY(0.0f);
  auto modelMatrix = DirectX::XMMatrixMultiply(scale, rotate);
  //modelMatrix = DirectX::XMMatrixIdentity();
  //modelMatrix = DirectX::XMMatrixTranslation(0.0f, 0.0f, 1.0f);
  DirectX::XMStoreFloat4x4(&modelToWorld_, modelMatrix);
  //
  DirectX::XMVECTOR pos = DirectX::XMVectorSet(0.0f, 0.0f, -30.9f, 0.0f);
  DirectX::XMVECTOR target = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
  DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

  auto viewMatrix = DirectX::XMMatrixLookAtLH(
    pos, target, up);
  DirectX::XMStoreFloat4x4(&view_, viewMatrix);
}

void phtm::Camera::SetPerspective(float verticalFOV, float aspectRatio)
{
  auto projMatrix = DirectX::XMMatrixPerspectiveFovLH(
    verticalFOV, aspectRatio, 0.001f, 1000.0f);
  DirectX::XMStoreFloat4x4(&projection_, projMatrix);
}
