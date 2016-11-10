#include "SimpleShader.h"
#include "Vertex.h"
#include <d3dcompiler.h>

static HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
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

bool phtm::SimpleShader::Initialize(ID3D11Device *d3dDevice)
{
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
    &vertexShader_);
  if (FAILED(hr))
  {
    vsBlob->Release();
    return false;
  }
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
    &vertexLayout_);
  vsBlob->Release();
  if (FAILED(hr))
    return false;

  ID3DBlob *psBlob = nullptr;
  hr = CompileShaderFromFile(
    L"shader.fx", "PS", "ps_4_0", &psBlob);
  if (FAILED(hr))
  {
    return false;
  }
  hr = d3dDevice->CreatePixelShader(
    psBlob->GetBufferPointer(),
    psBlob->GetBufferSize(),
    nullptr,
    &pixelShader_);
  psBlob->Release();
  if (FAILED(hr))
    return false;

  D3D11_BUFFER_DESC constBufferDesc;
  ZeroMemory(&constBufferDesc, sizeof(constBufferDesc));
  constBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  constBufferDesc.ByteWidth = sizeof(Camera);
  constBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  hr = d3dDevice->CreateBuffer(&constBufferDesc, nullptr, &constBuffer_);
  if (FAILED(hr))
    return false;
  return true;
}

void phtm::SimpleShader::Render(ID3D11DeviceContext *context, RawModel &rawModel, Camera &camera)
{
  context->UpdateSubresource(constBuffer_, 0, nullptr, &camera, 0, 0);

  context->IASetInputLayout(vertexLayout_);
  UINT stride1 = sizeof(Vertex);
  UINT offset1 = 0;
  context->IASetVertexBuffers(0, 1, &rawModel.vertexBuffer_, &stride1, &offset1);
  context->IASetIndexBuffer(rawModel.indexBuffer_, DXGI_FORMAT_R32_UINT, 0);
  context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  context->VSSetShader(vertexShader_, nullptr, 0);
  context->PSSetShader(pixelShader_, nullptr, 0);
  context->VSSetConstantBuffers(0, 1, &constBuffer_);
  context->DrawIndexed(rawModel.indexCount_, 0, 0);
};

