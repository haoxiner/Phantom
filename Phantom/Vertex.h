#pragma once
#include <DirectXMath.h>

namespace phtm
{
class Vertex
{
public:
  Vertex() {}
  Vertex(
    float x, float y, float z,
    float nx, float ny, float nz,
    float s, float t,
    float tx, float ty, float tz);
  DirectX::XMFLOAT3 position_;
  DirectX::XMFLOAT3 normal_;
  DirectX::XMFLOAT2 texCoord_;
  DirectX::XMFLOAT3 tangent_;
};
}