#pragma once
#include "Game.h"
#include "Engine.h"
#include "RenderingSystem.h"
#include "Player.h"

namespace phtm
{
class PhantomGame : public Game
{
public:
  PhantomGame();
  virtual ~PhantomGame();
  virtual void Start();
  virtual void Update(float deltaTimeInSeconds);
  virtual void End();
private:
  Engine engine_;
  Message message_;
  RenderingSystem renderingSystem_;
  Player player;
};
}