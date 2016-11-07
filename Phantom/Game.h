#pragma once
namespace phtm
{
class Game
{
public:
  Game() {}
  virtual ~Game() = 0;
  virtual void Start() = 0;
  virtual void Update(float deltaTimeInSeconds) = 0;
  virtual void End() = 0;
};
}