#include "Game.h"
#include "Vertex.h"
#include "Terrain.h"
#include <fstream>

phtm::Game::Game()
  :renderingSystem_(nullptr),
  player_(nullptr)
{
}

phtm::Game::~Game()
{
}

void phtm::Game::StartGame()
{
  renderingSystem_ = new RenderingSystem(&graphics_, screenWidth_, screenHeight_);
  movementSystem_ = new MovementSystem();
  resourceLoader_.Initialize(&graphics_);

  resourceLoader_.LoadRMD(componentCollection_.renderingComponents_[0].rawModel_, "D:/GameDev/Resources/knight.rmd");
  // player
  componentCollection_.movementComponents_[0].SetActive(true);
  componentCollection_.renderingComponents_[0].SetActive(true);
  componentCollection_.movementComponents_[0].position_ = DirectX::XMFLOAT3(400, 0, 400);
  componentCollection_.renderingComponents_[0].position_ = &componentCollection_.movementComponents_[0].position_;
  componentCollection_.renderingComponents_[0].rotation_ = &componentCollection_.movementComponents_[0].instantRotation_;
  player_ = new Player(&componentCollection_.movementComponents_[0],&componentCollection_.renderingComponents_[0]);
  
  // terrain
  componentCollection_.movementComponents_[1].SetActive(false);
  componentCollection_.renderingComponents_[1].SetActive(true);
  componentCollection_.movementComponents_[1].position_ = DirectX::XMFLOAT3(0, 0, 0);
  componentCollection_.renderingComponents_[1].position_ = &componentCollection_.movementComponents_[1].position_;
  componentCollection_.renderingComponents_[1].rotation_ = &componentCollection_.movementComponents_[1].instantRotation_;
  //auto terrain = new Terrain(&componentCollection_.movementComponents_[1], &componentCollection_.renderingComponents_[1]);
  std::vector<Vertex> terrainVertices;
  std::vector<int> terrainIndices;
  Terrain::GenerateTerrain(800, 256, terrainVertices, terrainIndices);
  resourceLoader_.LoadRawModel(
    componentCollection_.renderingComponents_[1].rawModel_,
    terrainVertices, terrainIndices);

  message_.componentCollection_ = &componentCollection_;
  message_.input_ = &(inputHandler_.input_);
  message_.camera_ = &camera_;
  message_.player_ = player_;

  engine_.AddSystem(movementSystem_);
  engine_.AddSystem(renderingSystem_);
  
  engine_.AddEntity(player_);
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
  if (renderingSystem_) delete renderingSystem_;
}
