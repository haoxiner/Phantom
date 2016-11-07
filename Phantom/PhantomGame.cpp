#include "PhantomGame.h"

phtm::PhantomGame::PhantomGame()
{
}

phtm::PhantomGame::~PhantomGame()
{
}

void phtm::PhantomGame::Start()
{
  engine_.AddSystem(&renderingSystem_);
}

void phtm::PhantomGame::Update(float deltaTimeInSeconds)
{
  message_.deltaTimeInSeconds_ = deltaTimeInSeconds;
  engine_.Update(message_);
}

void phtm::PhantomGame::End()
{
}
