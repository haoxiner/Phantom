#include "DeferredBuffers.h"
#include "Release.h"

phtm::DeferredBuffers::DeferredBuffers()
  :depthStencilView_(nullptr), depthStencilTexture_(nullptr)
{
  for (int i = 0; i < BUFFER_COUNT; i++)
  {
    textures_[i] = nullptr;
    renderTargetViews_[i] = nullptr;
    shaderResourceViews_[i] = nullptr;
  }
}

phtm::DeferredBuffers::~DeferredBuffers()
{
}

bool phtm::DeferredBuffers::Initialize(
  ID3D11Device *d3dDevice,
  int textureWidth, int textureHeight,
  float screenDepth, float screenNear)
{
  
  HRESULT result;
  width_ = textureWidth;
  height_ = textureHeight;

  D3D11_TEXTURE2D_DESC textureDesc;
  ZeroMemory(&textureDesc, sizeof(textureDesc));
  textureDesc.Width = width_;
  textureDesc.Height = height_;
  textureDesc.MipLevels = 1;
  textureDesc.ArraySize = 1;
  textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
  textureDesc.SampleDesc.Count = 1;
  textureDesc.SampleDesc.Quality = 0;
  textureDesc.Usage = D3D11_USAGE_DEFAULT;
  textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
  textureDesc.CPUAccessFlags = 0;
  textureDesc.MiscFlags = 0;
  for (int i = 0; i < BUFFER_COUNT; i++)
  {
    result = d3dDevice->CreateTexture2D(&textureDesc, nullptr, &textures_[i]);
    if (FAILED(result))
    {
      return false;
    }
  }

  D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
  renderTargetViewDesc.Format = textureDesc.Format;
  renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
  renderTargetViewDesc.Texture2D.MipSlice = 0;
  for (int i = 0; i < BUFFER_COUNT; i++)
  {
    result = d3dDevice->CreateRenderTargetView(textures_[i], &renderTargetViewDesc, &renderTargetViews_[i]);
    if (FAILED(result))
    {
      return false;
    }
  }

  D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
  shaderResourceViewDesc.Format = textureDesc.Format;
  shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
  shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
  shaderResourceViewDesc.Texture2D.MipLevels = 1;
  for (int i = 0; i < BUFFER_COUNT; i++)
  {
    result = d3dDevice->CreateShaderResourceView(textures_[i], &shaderResourceViewDesc, &shaderResourceViews_[i]);
    if (FAILED(result))
    {
      return false;
    }
  }

  D3D11_TEXTURE2D_DESC depthTextureDesc;
  depthTextureDesc.Width = width_;
  depthTextureDesc.Height = height_;
  depthTextureDesc.MipLevels = 1;
  depthTextureDesc.ArraySize = 1;
  depthTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  depthTextureDesc.SampleDesc.Count = 1;
  depthTextureDesc.SampleDesc.Quality = 0;
  depthTextureDesc.Usage = D3D11_USAGE_DEFAULT;
  depthTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
  depthTextureDesc.CPUAccessFlags = 0;
  depthTextureDesc.MiscFlags = 0;
  result = d3dDevice->CreateTexture2D(&depthTextureDesc, nullptr, &depthStencilTexture_);
  if (FAILED(result))
  {
    return false;
  }
  
  D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
  depthStencilViewDesc.Format = depthTextureDesc.Format;
  depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
  depthStencilViewDesc.Texture2D.MipSlice = 0;
  result = d3dDevice->CreateDepthStencilView(depthStencilTexture_, &depthStencilViewDesc, &depthStencilView_);
  if (FAILED(result))
  {
    return false;
  }

  viewport_.Width = static_cast<float>(width_);
  viewport_.Height = static_cast<float>(height_);
  viewport_.MinDepth = 0.0f;
  viewport_.MaxDepth = 1.0f;
  viewport_.TopLeftX = 0.0f;
  viewport_.TopLeftY = 0.0f;
  return true;
}

void phtm::DeferredBuffers::Shutdown()
{
  Release(depthStencilView_);
  Release(depthStencilTexture_);
  for (int i = 0; i < BUFFER_COUNT; i++)
  {
    Release(renderTargetViews_[i]);
    Release(shaderResourceViews_[i]);
    Release(textures_[i]);
  }
}

void phtm::DeferredBuffers::SetRenderTargets(ID3D11DeviceContext *deviceContext)
{
  deviceContext->OMSetRenderTargets(BUFFER_COUNT, renderTargetViews_, depthStencilView_);
  deviceContext->RSSetViewports(1, &viewport_);
}
