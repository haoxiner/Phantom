#pragma once
#include <DirectXMath.h>

namespace phtm
{
class Vertex
{
public:
  Vertex(DirectX::XMFLOAT3 &position):position_(position){}
  DirectX::XMFLOAT3 position_;
  //DirectX::XMFLOAT3 normal_;
  //DirectX::XMFLOAT2 texCoord_;
};
}