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
  virtual bool Initialize();
  virtual void Update(Message &message);
  virtual void CleanUp();
private:
  Graphics *graphics_;
  SimpleShader shader_;
};
}