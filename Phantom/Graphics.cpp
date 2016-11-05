#include "Graphics.h"
#include <directxcolors.h>

phtm::Graphics::Graphics()
  :immediateContext_(nullptr), renderTargetView_(nullptr),
  swapChain_(nullptr), d3dDevice_(nullptr),
  depthStencilView_(nullptr), depthStencilBuffer_(nullptr)
{
}

bool phtm::Graphics::Initialize(HWND hWnd)
{
  HRESULT hr = S_OK;
  UINT createDeviceFlags = 0;
#ifdef _DEBUG
  createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
  D3D_DRIVER_TYPE driverTypes[] =
  {
    D3D_DRIVER_TYPE_HARDWARE/*,
    D3D_DRIVER_TYPE_WARP,
    D3D_DRIVER_TYPE_REFERENCE,*/
  };
  UINT numDriverTypes = ARRAYSIZE(driverTypes);
  D3D_FEATURE_LEVEL featureLevels[] =
  {
    D3D_FEATURE_LEVEL_11_0
  };
  UINT numFeatureLevels = ARRAYSIZE(featureLevels);
  for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
  {
    driverType_ = driverTypes[driverTypeIndex];
    hr = D3D11CreateDevice(nullptr, driverType_, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
      D3D11_SDK_VERSION, &d3dDevice_, &featureLevel_, &immediateContext_);
    if (SUCCEEDED(hr))
      break;
  }
  if (FAILED(hr))
    return false;
  // Obtain DXGI factory from device (since we used nullptr for pAdapter above)
  IDXGIFactory1* dxgiFactory = nullptr;
  {
    IDXGIDevice* dxgiDevice = nullptr;
    hr = d3dDevice_->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
    if (SUCCEEDED(hr))
    {
      IDXGIAdapter* adapter = nullptr;
      hr = dxgiDevice->GetAdapter(&adapter);
      if (SUCCEEDED(hr))
      {
        hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory));
        adapter->Release();
      }
      dxgiDevice->Release();
    }
  }
  if (FAILED(hr))
    return false;
  RECT rc;
  GetClientRect(hWnd, &rc);
  UINT width = rc.right - rc.left;
  UINT height = rc.bottom - rc.top;
  // DirectX 11.0 systems
  DXGI_SWAP_CHAIN_DESC sd;
  ZeroMemory(&sd, sizeof(sd));
  sd.BufferCount = 1;
  sd.BufferDesc.Width = width;
  sd.BufferDesc.Height = height;
  sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  sd.BufferDesc.RefreshRate.Numerator = 60;
  sd.BufferDesc.RefreshRate.Denominator = 1;
  sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  sd.OutputWindow = hWnd;
  sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
  // MSAA
  sd.SampleDesc.Count = 1;
  sd.SampleDesc.Quality = 0;
  // Full Screen
  sd.Windowed = FALSE;
  sd.Flags = 0;
  hr = dxgiFactory->CreateSwapChain(d3dDevice_, &sd, &swapChain_);
  // block the ALT+ENTER shortcut (switch between full screen and window)
  //dxgiFactory->MakeWindowAssociation(hWnd, DXGI_MWA_NO_ALT_ENTER);
  dxgiFactory->Release();
  if (FAILED(hr))
    return false;
  // Create a render target view
  ID3D11Texture2D* pBackBuffer = nullptr;
  hr = swapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
  if (FAILED(hr))
    return false;
  hr = d3dDevice_->CreateRenderTargetView(pBackBuffer, nullptr, &renderTargetView_);
  pBackBuffer->Release();
  if (FAILED(hr))
    return false;

  // Depth/Stencil Buffer
  D3D11_TEXTURE2D_DESC depthStencilDesc;
  ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
  depthStencilDesc.Width = width;
  depthStencilDesc.Height = height;
  depthStencilDesc.MipLevels = 1;
  depthStencilDesc.ArraySize = 1;
  depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  depthStencilDesc.SampleDesc.Count = 1;
  depthStencilDesc.SampleDesc.Quality = 0;
  depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
  depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
  depthStencilDesc.CPUAccessFlags = 0;
  depthStencilDesc.MiscFlags = 0;
  hr = d3dDevice_->CreateTexture2D(&depthStencilDesc, nullptr, &depthStencilBuffer_);
  if (FAILED(hr))
    return false;
  hr = d3dDevice_->CreateDepthStencilView(depthStencilBuffer_, nullptr, &depthStencilView_);
  if (FAILED(hr))
    return false;

  immediateContext_->OMSetRenderTargets(1, &renderTargetView_, nullptr);
  // Setup the viewport
  D3D11_VIEWPORT vp;
  vp.Width = (FLOAT)width;
  vp.Height = (FLOAT)height;
  vp.MinDepth = 0.0f;
  vp.MaxDepth = 1.0f;
  vp.TopLeftX = 0;
  vp.TopLeftY = 0;
  immediateContext_->RSSetViewports(1, &vp);
  return true;
}

void phtm::Graphics::Update()
{
  immediateContext_->ClearRenderTargetView(renderTargetView_, DirectX::Colors::AntiqueWhite);
  swapChain_->Present(0, 0);
}

void phtm::Graphics::Shutdown()
{
  if (immediateContext_) immediateContext_->ClearState();

  if (depthStencilBuffer_) depthStencilBuffer_->Release();
  if (depthStencilView_) depthStencilView_->Release();
  
  if (renderTargetView_) renderTargetView_->Release();
  
  if (swapChain_) swapChain_->Release();
  
  if (immediateContext_) immediateContext_->Release();
  if (d3dDevice_) d3dDevice_->Release();
}
