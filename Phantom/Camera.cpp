#include "Camera.h"
#include <cmath>

phtm::Camera::Camera()
{
  DirectX::XMVECTOR pos = DirectX::XMVectorSet(0.0f, 0.0f, -5.0f, 1.0f);
  DirectX::XMVECTOR target = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
  DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

  view_ = DirectX::XMMatrixLookAtLH(
    pos, target, up);
}

void phtm::Camera::SetPerspective(float verticalFOV, float aspectRatio)
{
  /*projection_ = DirectX::XMMatrixPerspectiveFovLH(
    verticalFOV, aspectRatio, 0.1f, 1000.0f);*/
  projection_ = DirectX::XMMatrixIdentity();
}
