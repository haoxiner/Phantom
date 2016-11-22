#include "RenderingSystem.h"
#include "Vertex.h"
#include "Camera.h"
#include "ComponentCollection.h"
#include <d3dcompiler.h>

static HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob **ppBlobOut);

phtm::RenderingSystem::RenderingSystem(Graphics *graphics, int screenWidth, int screenHeight)
  :graphics_(graphics)
{
  float verticalFOV = 0.5f*3.141592654f;
  float aspectRatio = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);
  auto projMatrix = DirectX::XMMatrixPerspectiveFovLH(
    verticalFOV, aspectRatio, 0.001f, 1000.0f);
  DirectX::XMStoreFloat4x4(&changeOnResize.projection_, projMatrix);
}

bool phtm::RenderingSystem::Initialize()
{
  auto d3dDevice = graphics_->GetD3DDevice();
  bool success = CreateSimpleVertexShader(d3dDevice);
  if (!success)
    return false;
  success = CreateSimplePixelShader(d3dDevice);
  if (!success)
    return false;

  ID3D11Buffer *cbChangeOnResize = nullptr;
  D3D11_BUFFER_DESC constBufferDesc;
  ZeroMemory(&constBufferDesc, sizeof(constBufferDesc));
  constBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
  constBufferDesc.ByteWidth = sizeof(ChangeOnResize);
  constBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  D3D11_SUBRESOURCE_DATA initData;
  ZeroMemory(&initData, sizeof(initData));
  initData.pSysMem = &changeOnResize;
  auto hr = d3dDevice->CreateBuffer(&constBufferDesc, &initData, &cbChangeOnResize);
  if (FAILED(hr))
    return false;
  constantBuffers_.push_back(cbChangeOnResize);

  ID3D11Buffer *cbChangeEveryFrame = nullptr;
  ZeroMemory(&constBufferDesc, sizeof(constBufferDesc));
  constBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
  constBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  constBufferDesc.ByteWidth = sizeof(ChangeEveryFrame);
  constBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  ZeroMemory(&initData, sizeof(initData));
  initData.pSysMem = &changeEveryFrame;
  hr = d3dDevice->CreateBuffer(&constBufferDesc, &initData, &cbChangeEveryFrame);
  
  if (FAILED(hr))
    return false;
  constantBuffers_.push_back(cbChangeEveryFrame);
  return true;
}

void phtm::RenderingSystem::Update(Message &message)
{
  message.camera_->Update(message);
  changeEveryFrame.view_ = message.camera_->view_;
  auto d3dContext = graphics_->GetD3DDeviceContext();
  D3D11_MAPPED_SUBRESOURCE mappedResource;
  //ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));
  
  for (auto &renderingComponent : message.componentCollection_->renderingComponents_)
  {
    if (!renderingComponent.IsActive())
    {
      continue;
    }
    auto rotate = DirectX::XMMatrixRotationY(-*renderingComponent.rotation_);
    auto translate = DirectX::XMMatrixTranslation(
      renderingComponent.position_->x,
      renderingComponent.position_->y,
      renderingComponent.position_->z);
    auto modelMatrix = DirectX::XMMatrixMultiply(rotate, translate);
    DirectX::XMStoreFloat4x4(&changeEveryFrame.modelToWorld, modelMatrix);

    //	Disable GPU access to the vertex buffer data.
    d3dContext->Map(constantBuffers_.back(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    //	Update the vertex buffer here.
    memcpy(mappedResource.pData, &changeEveryFrame, sizeof(ChangeEveryFrame));
    //	Reenable GPU access to the vertex buffer data.
    d3dContext->Unmap(constantBuffers_.back(), 0);
    SimpleRender(graphics_->GetD3DDeviceContext(), renderingComponent.rawModel_, *(message.camera_));
  }
}

void phtm::RenderingSystem::SimpleRender(ID3D11DeviceContext *context, RawModel &rawModel, Camera &camera)
{
  context->IASetInputLayout(inputLayouts_[0]);
  UINT stride1 = sizeof(Vertex);
  UINT offset1 = 0;
  context->IASetVertexBuffers(0, 1, &rawModel.vertexBuffer_, &stride1, &offset1);
  context->IASetIndexBuffer(rawModel.indexBuffer_, DXGI_FORMAT_R32_UINT, 0);
  context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  context->VSSetShader(vertexShaders_[0], nullptr, 0);
  context->PSSetShader(pixelShaders_[0], nullptr, 0);
  context->VSSetConstantBuffers(0, 1, &constantBuffers_[0]);
  context->VSSetConstantBuffers(1, 1, &constantBuffers_[1]);
  context->DrawIndexed(rawModel.indexCount_, 0, 0);
}

void phtm::RenderingSystem::CleanUp()
{
  for (auto cbuffer : constantBuffers_)
  {
    cbuffer->Release();
  }
  for (auto inputLayout : inputLayouts_)
  {
    inputLayout->Release();
  }
  for (auto vs : vertexShaders_)
  {
    vs->Release();
  }
  for (auto ps : pixelShaders_)
  {
    ps->Release();
  }
}

bool phtm::RenderingSystem::CreateSimpleVertexShader(ID3D11Device *d3dDevice)
{
  ID3D11VertexShader *vertexShader;
  ID3DBlob *vsBlob = nullptr;
  HRESULT hr = CompileShaderFromFile(
    L"shader.fx", "VS", "vs_4_0", &vsBlob);
  if (FAILED(hr))
  {
    return false;
  }
  d3dDevice->CreateVertexShader(
    vsBlob->GetBufferPointer(),
    vsBlob->GetBufferSize(),
    nullptr,
    &vertexShader);
  if (FAILED(hr))
  {
    vsBlob->Release();
    return false;
  }
  vertexShaders_.push_back(vertexShader);

  ID3D11InputLayout *vertexLayout = nullptr;
  D3D11_INPUT_ELEMENT_DESC layout[] =
  {
    {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
    {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}
  };
  int numElements = ARRAYSIZE(layout);
  hr = d3dDevice->CreateInputLayout(
    layout, numElements,
    vsBlob->GetBufferPointer(),
    vsBlob->GetBufferSize(),
    &vertexLayout);
  vsBlob->Release();
  if (FAILED(hr))
    return false;
  inputLayouts_.push_back(vertexLayout);
  return true;
}

bool phtm::RenderingSystem::CreateSimplePixelShader(ID3D11Device *d3dDevice)
{
  ID3D11PixelShader *pixelShader = nullptr;
  ID3DBlob *psBlob = nullptr;
  HRESULT hr = CompileShaderFromFile(
    L"shader.fx", "PS", "ps_4_0", &psBlob);
  if (FAILED(hr))
  {
    return false;
  }
  hr = d3dDevice->CreatePixelShader(
    psBlob->GetBufferPointer(),
    psBlob->GetBufferSize(),
    nullptr,
    &pixelShader);
  psBlob->Release();
  if (FAILED(hr))
    return false;
  pixelShaders_.push_back(pixelShader);
  return true;
}

HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob **ppBlobOut)
{
  HRESULT hr = S_OK;

  DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
  // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
  // Setting this flag improves the shader debugging experience, but still allows 
  // the shaders to be optimized and to run exactly the way they will run in 
  // the release configuration of this program.
  dwShaderFlags |= D3DCOMPILE_DEBUG;

  // Disable optimizations to further improve shader debugging
  dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

  ID3DBlob* pErrorBlob = nullptr;
  hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
    dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
  if (FAILED(hr))
  {
    if (pErrorBlob)
    {
      OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
      pErrorBlob->Release();
    }
    return hr;
  }
  if (pErrorBlob) pErrorBlob->Release();

  return S_OK;
}