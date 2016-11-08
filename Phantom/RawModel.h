#pragma once
#include <d3d11.h>

namespace phtm
{
class RawModel
{
public:
  ID3D11Buffer *vertexBuffer_;
  ID3D11Buffer *indexBuffer_;
};
}