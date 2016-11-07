#pragma once
#include <d3d11.h>

namespace phtm
{
class Graphics
{
public:
  Graphics();
  bool Initialize(HWND hWnd);
  void Update();
  void Shutdown();
  void ClearScreen();
  ID3D11Device *GetD3DDevice();
  ID3D11DeviceContext *GetD3DDeviceContext();
  void SetViewPort(int width, int height);
private:
  bool InitializeDevice();
  bool InitializeSwapChain(HWND hWnd, int width, int height);
  bool InitializeDepthStencil(int width, int height);
  bool InitializeRenderTargetView();
  // directx 11.0
  D3D_DRIVER_TYPE driverType_;
  D3D_FEATURE_LEVEL featureLevel_;
  ID3D11Device *d3dDevice_;
  ID3D11DeviceContext *immediateContext_;
  IDXGISwapChain *swapChain_;
  ID3D11RenderTargetView *renderTargetView_;
  ID3D11DepthStencilView *depthStencilView_;
  ID3D11Texture2D *depthStencilBuffer_;
};
}