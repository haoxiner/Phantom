#include "Game.h"
#include "Vertex.h"
#include <fstream>

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
  auto &rawModel = componentCollection_.renderingComponents_[0].rawModel_;

  std::ifstream rmd("D:/GameDev/Resources/knight.rmd", std::ios::binary);
  int numOfVertices, numOfFaces;
  rmd.read((char*)&numOfVertices, sizeof(int));
  rmd.read((char*)&numOfFaces, sizeof(int));
  rawModel.indexCount_ = numOfFaces * 3;
  Vertex *vertices = new Vertex[numOfVertices];
  rmd.read((char*)vertices, numOfVertices * sizeof(Vertex));

  D3D11_BUFFER_DESC bufferDesc = {0};
  bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
  bufferDesc.ByteWidth = sizeof(Vertex) * numOfVertices;
  bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  D3D11_SUBRESOURCE_DATA initData = {0};
  initData.pSysMem = vertices;
  HRESULT hr = graphics_.GetD3DDevice()->CreateBuffer(
    &bufferDesc, &initData, &rawModel.vertexBuffer_);
  delete vertices;
  if (FAILED(hr))
  {
    return;
  }
  
  int *indices = new int[numOfFaces * 3];
  rmd.read((char*)indices, numOfFaces * 3 * sizeof(int));
  D3D11_BUFFER_DESC indexBufferDesc = {0};
  indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
  indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
  indexBufferDesc.ByteWidth = sizeof(int) * numOfFaces * 3;
  D3D11_SUBRESOURCE_DATA indexData = {0};
  indexData.pSysMem = indices;
  hr = graphics_.GetD3DDevice()->CreateBuffer(&indexBufferDesc, &indexData, &rawModel.indexBuffer_);
  delete indices;
  if (FAILED(hr))
  {
    return;
  }

  camera_.SetPerspective(
    0.5f*3.141592654f,
    static_cast<float>(screenWidth_)/static_cast<float>(screenHeight_));
  message_.componentCollection_ = &componentCollection_;
  message_.input_ = &(inputHandler_.input_);
  message_.camera_ = &camera_;

  engine_.AddSystem(renderingSystem_);
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
  if (inputHandler_.input_.LeftHorizontalAxisX() > 0)
  {
    engine_.Update(message_);
  }
  
  graphics_.Update();
}

void phtm::Game::EndGame()
{
  engine_.Shutdown();
  if (renderingSystem_) delete renderingSystem_;
}
