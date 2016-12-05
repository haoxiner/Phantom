#include "DeferredRenderer.h"
#include "ShaderUtil.h"
#include "Release.h"

phtm::DeferredRenderer::DeferredRenderer()
  :vertexShader_(nullptr), pixelShader_(nullptr),
  vertexLayout_(nullptr), cbImmutable_(nullptr),
  cbPerFrame_(nullptr), cbPerObject_(nullptr)
{
}

phtm::DeferredRenderer::~DeferredRenderer()
{
}

bool phtm::DeferredRenderer::Initialize(ID3D11Device *device, float aspectRatio)
{
  if (!InitializeShader(device))
  {
    return false;
  }
  if (!InitializeConstantBuffer(device, aspectRatio))
  {
    return false;
  }
  return true;
}

void phtm::DeferredRenderer::Render(ID3D11DeviceContext *deviceContext)
{
  deviceContext->IASetInputLayout(vertexLayout_);
  deviceContext->VSSetShader(vertexShader_, nullptr, 0);
  deviceContext->PSSetShader(pixelShader_, nullptr, 0);

}

bool phtm::DeferredRenderer::InitializeShader(ID3D11Device *device)
{
  // compile vertex shader
  ID3DBlob *vsBlob = nullptr;
  HRESULT result = CompileShaderFromFile(
    L"deferred.fx", "VS", "vs_4_0", &vsBlob);
  if (FAILED(result))
  {
    return false;
  }
  device->CreateVertexShader(
    vsBlob->GetBufferPointer(),
    vsBlob->GetBufferSize(),
    nullptr,
    &vertexShader_);
  if (FAILED(result))
  {
    vsBlob->Release();
    return false;
  }

  // set input layout
  D3D11_INPUT_ELEMENT_DESC layout[] =
  {
    {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
    {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}
  };
  int numElements = ARRAYSIZE(layout);
  result = device->CreateInputLayout(
    layout, numElements,
    vsBlob->GetBufferPointer(),
    vsBlob->GetBufferSize(),
    &vertexLayout_);
  vsBlob->Release();
  if (FAILED(result))
  {
    return false;
  }

  // compile pixel shader
  ID3DBlob *psBlob = nullptr;
  HRESULT hr = CompileShaderFromFile(
    L"deferred.fx", "PS", "ps_4_0", &psBlob);
  if (FAILED(result))
  {
    return false;
  }
  result = device->CreatePixelShader(
    psBlob->GetBufferPointer(),
    psBlob->GetBufferSize(),
    nullptr,
    &pixelShader_);
  psBlob->Release();
  if (FAILED(result))
  {
    return false;
  }

  return true;
}

bool phtm::DeferredRenderer::InitializeConstantBuffer(ID3D11Device *device, float aspectRatio)
{
  D3D11_BUFFER_DESC constBufferDesc;
  ZeroMemory(&constBufferDesc, sizeof(constBufferDesc));
  constBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
  constBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  constBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

  PerObjectBuffer perObjectBuffer;
  constBufferDesc.ByteWidth = sizeof(perObjectBuffer);
  auto result = device->CreateBuffer(&constBufferDesc, nullptr, &cbPerObject_);
  if (FAILED(result))
  {
    return false;
  }

  PerFrameBuffer perFrameBuffer;
  constBufferDesc.ByteWidth = sizeof(perFrameBuffer);
  result = device->CreateBuffer(&constBufferDesc, nullptr, &cbPerFrame_);
  if (FAILED(result))
  {
    return false;
  }

  ImmutableBuffer immutableBuffer;
  constBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
  constBufferDesc.ByteWidth = sizeof(immutableBuffer);
  constBufferDesc.CPUAccessFlags = 0;
  float verticalFOV = 0.5f*3.141592654f;
  auto projMatrix = DirectX::XMMatrixPerspectiveFovLH(
    verticalFOV, aspectRatio, 0.001f, 1000.0f);
  DirectX::XMStoreFloat4x4(&immutableBuffer.projection_, projMatrix);
  D3D11_SUBRESOURCE_DATA initData;
  ZeroMemory(&initData, sizeof(initData));
  initData.pSysMem = &immutableBuffer;
  result = device->CreateBuffer(&constBufferDesc, nullptr, &cbImmutable_);
  if (FAILED(result))
  {
    return false;
  }

  return true;
}

void phtm::DeferredRenderer::Shutdown()
{
  Release(vertexShader_);
  Release(pixelShader_);
  Release(vertexLayout_);
  Release(cbImmutable_);
  Release(cbPerFrame_);
  Release(cbPerObject_);
}