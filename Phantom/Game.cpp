#include "Game.h"
#include "Vertex.h"

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
  Vertex vertices[] =
  {
    DirectX::XMFLOAT3(0.0f, 0.5f, 0.5f),
    DirectX::XMFLOAT3(0.5f, -0.5f, 0.5f),
    DirectX::XMFLOAT3(-0.5f, -0.5f, 0.5f)
  };
  D3D11_BUFFER_DESC bufferDesc = {0};
  bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
  bufferDesc.ByteWidth = sizeof(Vertex) * 3;
  bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  D3D11_SUBRESOURCE_DATA initData = {0};
  initData.pSysMem = vertices;
  HRESULT hr = graphics_.GetD3DDevice()->CreateBuffer(
    &bufferDesc, &initData, &rawModel.vertexBuffer_);
  if (FAILED(hr))
  {
    return;
  }
  int indices[] =
  {
    0,1,2
  };
  D3D11_BUFFER_DESC indexBufferDesc = {0};
  indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
  indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
  indexBufferDesc.ByteWidth = sizeof(int) * 3;
  D3D11_SUBRESOURCE_DATA indexData = {0};
  indexData.pSysMem = indices;
  hr = graphics_.GetD3DDevice()->CreateBuffer(&indexBufferDesc, &indexData, &rawModel.indexBuffer_);
  if (FAILED(hr))
  {
    return;
  }

  message_.componentCollection_ = &componentCollection_;
  engine_.AddSystem(renderingSystem_);
  engine_.Start();

  running_ = true;
}

void phtm::Game::UpdateGame(float deltaTimeInSeconds)
{
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
