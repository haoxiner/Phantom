#pragma once
#include "RenderingComponent.h"
#include "MovementComponent.h"
#include <array>

namespace phtm
{
class ComponentCollection
{
public:
  // should put rendering component and a movement or position
  // component together (interleaved)
  // 1. movable rendering component
  // 2. static rendering component
  std::array<RenderingComponent, 2> renderingComponents_;
  std::array<MovementComponent, 2> movementComponents_;
private:

};
}