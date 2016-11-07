#include "Game.h"

phtm::Game::Game()
  :renderingSystem_(nullptr)
{
}

phtm::Game::~Game()
{
}

void phtm::Game::StartGame()
{
  renderingSystem_ = new RenderingSystem(&graphics_);
  running_ = renderingSystem_->Init();
  running_ = true;
  engine_.AddSystem(renderingSystem_);
  engine_.Start();
}

void phtm::Game::UpdateGame(float deltaTimeInSeconds)
{
  message_.deltaTimeInSeconds_ = deltaTimeInSeconds;
  engine_.Update(message_);
  graphics_.Update();
}

void phtm::Game::EndGame()
{
  engine_.Shutdown();
  if (renderingSystem_) delete renderingSystem_;
}
