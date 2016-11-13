#pragma once
#include <DirectXMath.h>

namespace phtm
{
class MovementComponent
{
public:
  DirectX::XMFLOAT3 position_;
  // 2D movement only
  DirectX::XMFLOAT2 direction_;
  float moveSpeed_;
  float rotateSpeed_;
  float upwardSpeed_;
  // instant value used in movement system
  DirectX::XMFLOAT2 instantDirection_;
  // make following calculation by SIMD
  // direction_ = normalize(direction_);
  // instantDirection_ = normalize(interp(normalize(instantDirection_),deltaTime*rotateSpeed,direction_));
  // if (instantDirection_ == direction_)
  // {
  //   velocity = instantDirection_*speed
  //   newPosition = deltaTime * velocity + oldPosition
  // }
};
}