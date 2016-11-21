#pragma once
#include "RawModel.h"
#include "Component.h"
#include <DirectXMath.h>

namespace phtm
{
class RenderingComponent : public Component
{
public:
  RawModel rawModel_;
  DirectX::XMFLOAT3 *position_;
  float *rotation_;
};
}