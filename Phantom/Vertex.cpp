#include "Vertex.h"

phtm::Vertex::Vertex(
  float x, float y, float z,
  float nx, float ny, float nz,
  float s, float t,
  float tx, float ty, float tz)
  :position_(x, y, z), normal_(nx, ny, nz),
  texCoord_(s, t), tangent_(tx, ty, tz)
{
}
