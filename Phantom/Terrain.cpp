#include "Terrain.h"

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
    for (int z = 0; z < VERTEX_COUNT; z++)
    {
      vertices.emplace_back(
        ((float)x) / (VERTEX_COUNT - 1) * SIZE,
        0.0f,
        ((float)z) / (VERTEX_COUNT - 1) * SIZE,
        0.0f,
        1.0f,
        0.0f,
        ((float)x) / (VERTEX_COUNT - 1),
        ((float)z) / (VERTEX_COUNT - 1),
        0.0f,0.0f,1.0f);
    }
  }
  for (int x = 0; x < VERTEX_COUNT - 1; x++)
  {
    for (int z = 0; z < VERTEX_COUNT - 1; z++)
    {
      int bottomLeft = x * VERTEX_COUNT + z;
      int bottomRight = bottomLeft + 1;
      int topLeft = (x + 1) * VERTEX_COUNT + z;
      int topRight = topLeft + 1;
      indices.push_back(bottomLeft);
      indices.push_back(topRight);
      indices.push_back(topLeft);
      indices.push_back(bottomLeft);
      indices.push_back(bottomRight);
      indices.push_back(topRight);
    }
  }
}