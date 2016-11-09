#pragma once
#include <DirectXMath.h>

namespace phtm
{
class Camera
{
public:
  Camera();
  void SetPerspective(float verticalFOV, float aspectRatio);
  DirectX::XMMATRIX view_;
  DirectX::XMMATRIX projection_;
};
}