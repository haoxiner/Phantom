#pragma once
#include <d3d11.h>
namespace phtm
{
class DeferredBuffers
{
public:
  DeferredBuffers();
  ~DeferredBuffers();
  bool Initialize(
    ID3D11Device *d3dDevice,
    int textureWidth, int textureHeight,
    float screenDepth, float screenNear);
  void Shutdown();
  void SetRenderTargets(ID3D11DeviceContext *deviceContext);
private:
  int width_;
  int height_;
  static const int BUFFER_COUNT = 2;
  ID3D11Texture2D *textures_[BUFFER_COUNT];
  ID3D11RenderTargetView *renderTargetViews_[BUFFER_COUNT];
  ID3D11ShaderResourceView *shaderResourceViews_[BUFFER_COUNT];
  ID3D11Texture2D *depthStencilTexture_;
  ID3D11DepthStencilView *depthStencilView_;
  D3D11_VIEWPORT viewport_;
};
}