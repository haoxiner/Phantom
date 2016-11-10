#include "RenderingSystem.h"
#include "Vertex.h"
#include <d3dcompiler.h>

static HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob **ppBlobOut);

phtm::RenderingSystem::RenderingSystem(Graphics *graphics)
  :graphics_(graphics)
{
  
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

  ID3D11Buffer *constBuffer;
  D3D11_BUFFER_DESC constBufferDesc;
  ZeroMemory(&constBufferDesc, sizeof(constBufferDesc));
  constBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  constBufferDesc.ByteWidth = sizeof(Camera);
  constBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  auto hr = d3dDevice->CreateBuffer(&constBufferDesc, nullptr, &constBuffer);
  if (FAILED(hr))
    return false;
  constantBuffers_.push_back(constBuffer);
  simpleRenderer_.Initialize(
    vertexShaders_.back(),
    inputLayouts_.back(),
    pixelShaders_.back(),
    constantBuffers_.back());
  return true;
}

void phtm::RenderingSystem::Update(Message &message)
{
  simpleRenderer_.Render(graphics_->GetD3DDeviceContext(), message.componentCollection_->renderingComponents_[0].rawModel_, *(message.camera_));
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