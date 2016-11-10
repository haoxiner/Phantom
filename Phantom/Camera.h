#pragma once
#include <DirectXMath.h>

namespace phtm
{
class Camera
{
public:
  Camera();
  void SetPerspective(float verticalFOV, float aspectRatio);
  DirectX::XMFLOAT4X4 modelToWorld_;
  DirectX::XMFLOAT4X4 view_;
  DirectX::XMFLOAT4X4 projection_;
};
}