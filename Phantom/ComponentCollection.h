#pragma once
#include "RenderingComponent.h"
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
  std::array<RenderingComponent, 20> renderingComponents_;
private:

};
}