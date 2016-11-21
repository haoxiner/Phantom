#pragma once
#include "Vertex.h"
#include "RenderingComponent.h"
#include "MovementComponent.h"
#include <vector>

namespace phtm
{
class Terrain
{
public:
  Terrain(
    MovementComponent *movementComponent,
    RenderingComponent *renderingComponent);
  static void GenerateTerrain(
    const int SIZE,
    const int VERTEX_COUNT,
    std::vector<Vertex> &vertices,
    std::vector<int> &indices);
private:
  MovementComponent *movementComponent_;
  RenderingComponent *renderingComponent_;
};
}
