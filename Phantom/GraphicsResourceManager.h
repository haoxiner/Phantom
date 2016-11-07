#pragma once
#include "Vertex.h"
#include <d3d11.h>
#include <vector>

namespace phtm
{
class GraphicsResourceManager
{
public:
  //int LoadMesh(std::vector<Vertex> vertices, std::vector<int> indices);
private:
  std::vector<ID3D11Buffer*> buffers_;
};
}