#pragma once
#include "System.h"
#include "Graphics.h"
#include "SimpleShader.h"

namespace phtm
{
class RenderingSystem : public System
{
public:
  RenderingSystem(Graphics *graphics);
  virtual ~RenderingSystem() {}
  virtual void Update(Message &message);
  bool Init();
private:
  Graphics *graphics_;
  SimpleShader shader_;
  ID3D11Buffer *buffer_;
};
}