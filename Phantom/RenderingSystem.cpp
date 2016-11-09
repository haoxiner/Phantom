#include "RenderingSystem.h"
#include "Vertex.h"

phtm::RenderingSystem::RenderingSystem(Graphics *graphics)
  :graphics_(graphics)
{
  
}

bool phtm::RenderingSystem::Initialize()
{
  bool success = shader_.Initialize(graphics_->GetD3DDevice());
  if (!success)
    return false;
  return true;
}

void phtm::RenderingSystem::Update(Message &message)
{
  shader_.Render(graphics_->GetD3DDeviceContext(), message.componentCollection_->renderingComponents_[0].rawModel_, *(message.camera_));
}

void phtm::RenderingSystem::CleanUp()
{
}