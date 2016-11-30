#include "Game.h"
#include "Vertex.h"
#include "Terrain.h"
#include <fstream>

phtm::Game::Game()
{
}

phtm::Game::~Game()
{
}

void phtm::Game::StartGame()
{
  renderingSystem_.Initialize(&graphics_, screenWidth_, screenHeight_);
  resourceLoader_.Initialize(&graphics_);

  // player
  resourceLoader_.LoadRMD(componentCollection_.renderingComponents_[0].rawModel_, "D:/GameDev/Resources/knight.rmd");
  componentCollection_.movementComponents_[0].SetActive(true);
  componentCollection_.renderingComponents_[0].SetActive(true);
  componentCollection_.movementComponents_[0].position_ = DirectX::XMFLOAT3(400, 0, 400);
  componentCollection_.renderingComponents_[0].position_ = &componentCollection_.movementComponents_[0].position_;
  componentCollection_.renderingComponents_[0].rotation_ = &componentCollection_.movementComponents_[0].instantRotation_;
  player_.Initialize(&componentCollection_.movementComponents_[0],&componentCollection_.renderingComponents_[0]);
  
  // terrain
  gameScene_.PrepareTerrain(componentCollection_, resourceLoader_);

  message_.componentCollection_ = &componentCollection_;
  message_.input_ = &(inputHandler_.input_);
  message_.camera_ = &camera_;
  message_.player_ = &player_;

  engine_.AddSystem(&movementSystem_);
  engine_.AddSystem(&renderingSystem_);
  
  engine_.AddEntity(&player_);
  if (!engine_.Start())
  {
    running_ = false;
  }
  else
  {
    running_ = true;
  }
}

void phtm::Game::UpdateGame(float deltaTimeInSeconds)
{
  if (inputHandler_.input_.Quit())
  {
    running_ = false;
    return;
  }
  graphics_.ClearScreen();
  message_.deltaTimeInSeconds_ = deltaTimeInSeconds;
  engine_.Update(message_);
  graphics_.Update();
}

void phtm::Game::EndGame()
{
  engine_.Shutdown();
}
