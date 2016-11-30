#pragma once
#include "Terrain.h"
#include "ComponentCollection.h"
#include "ResourceLoader.h"

namespace phtm
{
class GameScene
{
public:
  GameScene() {}
  void PrepareTerrain(ComponentCollection &componentCollection, ResourceLoader &resourceLoader);
  //Terrain terrain_;

};
}