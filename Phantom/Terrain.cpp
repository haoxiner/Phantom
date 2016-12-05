#include "Terrain.h"
#include <DirectXMath.h>

phtm::Terrain::Terrain(
  MovementComponent *movementComponent,
  RenderingComponent *renderingComponent)
  :movementComponent_(movementComponent),
  renderingComponent_(renderingComponent)
{
}

void phtm::Terrain::GenerateTerrain(
  const int SIZE, const int VERTEX_COUNT,
  std::vector<Vertex> &vertices,
  std::vector<int> &indices)
{
  for (int x = 0; x < VERTEX_COUNT; x++)
  {
    for (int y = 0; y < VERTEX_COUNT; y++)
    {
      vertices.emplace_back(
        ((float)x) / (VERTEX_COUNT - 1) * SIZE,
        ((float)y) / (VERTEX_COUNT - 1) * SIZE,
        0.0f,//0.3f*y*DirectX::XMScalarSin(0.1f*x) + 0.3f*x*DirectX::XMScalarCos(0.1f*y),
        0.0f,//-0.03f*y*DirectX::XMScalarCos(0.1f*y) - 0.3f*DirectX::XMScalarCos(0.1f*y),
        0.0f,
        1.0f,//-0.3f*y*DirectX::XMScalarSin(0.1f*x) + 0.03f*DirectX::XMScalarSin(0.1f*y),
        ((float)x) / (VERTEX_COUNT - 1),
        ((float)y) / (VERTEX_COUNT - 1),
        0.0f,0.0f,1.0f);
    }
  }
  for (int x = 0; x < VERTEX_COUNT - 1; x++)
  {
    for (int y = 0; y < VERTEX_COUNT - 1; y++)
    {
      int topLeft = x * VERTEX_COUNT + y;
      int bottomLeft = topLeft + 1;
      int topRight = (x + 1) * VERTEX_COUNT + y;
      int bottomRight = topRight + 1;
      
      indices.push_back(topLeft);
      indices.push_back(topRight);
      indices.push_back(bottomLeft);

      indices.push_back(bottomLeft);
      indices.push_back(topRight);
      indices.push_back(bottomRight);
    }
  }
}
