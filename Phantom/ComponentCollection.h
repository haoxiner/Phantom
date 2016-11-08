#pragma once
#include "RenderingComponent.h"
#include <array>

namespace phtm
{
class ComponentCollection
{
public:
  std::array<RenderingComponent, 20> renderingComponents_;
private:

};
}