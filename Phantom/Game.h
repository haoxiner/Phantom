#pragma once
#include "Application.h"
#include "Message.h"
#include "Engine.h"
#include "RenderingSystem.h"

namespace phtm
{
class Game : public Application
{
public:
  Game();
  virtual ~Game();
protected:
  virtual void StartGame();
  virtual void UpdateGame(float deltaTimeInSeconds);
  virtual void EndGame();
private:
  Message message_;
  Engine engine_;
  RenderingSystem *renderingSystem_;
};
}