#pragma once
#include "RawModel.h"
#include <DirectXMath.h>

namespace phtm
{
class RenderingComponent
{
public:
  RawModel rawModel_;
  DirectX::XMFLOAT3 *position_;
  DirectX::XMFLOAT2 *rotation_;
};
}