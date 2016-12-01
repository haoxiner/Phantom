#include "GameScene.h"

void phtm::GameScene::PrepareTerrain(
  ComponentCollection &componentCollection,
  ResourceLoader &resourceLoader)
{
  componentCollection.movementComponents_[1].SetActive(false);
  componentCollection.renderingComponents_[1].SetActive(true);
  componentCollection.movementComponents_[1].position_ = DirectX::XMFLOAT3(0, 0, 0);
  componentCollection.movementComponents_[1].instantRotation_ = 0.0f;
  componentCollection.renderingComponents_[1].position_ = &componentCollection.movementComponents_[1].position_;
  componentCollection.renderingComponents_[1].rotation_ = &componentCollection.movementComponents_[1].instantRotation_;
  //auto terrain = new Terrain(&componentCollection_.movementComponents_[1], &componentCollection_.renderingComponents_[1]);
  std::vector<Vertex> terrainVertices;
  std::vector<int> terrainIndices;
  Terrain::GenerateTerrain(100, 64, terrainVertices, terrainIndices);
  resourceLoader.LoadRawModel(
    componentCollection.renderingComponents_[1].rawModel_,
    terrainVertices, terrainIndices);
}
