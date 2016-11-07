#include "RenderingSystem.h"
#include "Vertex.h"

phtm::RenderingSystem::RenderingSystem(Graphics *graphics)
  :graphics_(graphics), buffer_(nullptr)
{
  
}

void phtm::RenderingSystem::Update(Message &message)
{
  graphics_->ClearScreen();
  shader_.Render(graphics_->GetD3DDeviceContext(), buffer_, sizeof(Vertex), 0);
}

bool phtm::RenderingSystem::Init()
{
  bool success = shader_.Initialize(graphics_->GetD3DDevice());
  if (!success)
    return false;
  Vertex vertices[] =
  {
    DirectX::XMFLOAT3(0.0f, 0.5f, 0.5f),
    DirectX::XMFLOAT3(0.5f, -0.5f, 0.5f),
    DirectX::XMFLOAT3(-0.5f, -0.5f, 0.5f)
  };
  D3D11_BUFFER_DESC bufferDesc = {0};
  bufferDesc.Usage = D3D11_USAGE_DEFAULT;
  bufferDesc.ByteWidth = sizeof(Vertex) * 3;
  bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bufferDesc.CPUAccessFlags = 0;
  D3D11_SUBRESOURCE_DATA initData = {0};
  initData.pSysMem = vertices;
  HRESULT hr = graphics_->GetD3DDevice()->CreateBuffer(
    &bufferDesc, &initData, &buffer_);
  if (FAILED(hr))
  {
    return false;
  }
  return true;
}
