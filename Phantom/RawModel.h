#pragma once
#include <d3d11.h>

namespace phtm
{
class RawModel
{
public:
  int indexCount_;
  ID3D11Buffer *vertexBuffer_;
  ID3D11Buffer *indexBuffer_;
};
}