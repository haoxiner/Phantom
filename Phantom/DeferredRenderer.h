#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

namespace phtm
{
class DeferredRenderer
{
public:
  DeferredRenderer();
  ~DeferredRenderer();
  bool Initialize(ID3D11Device *device, float aspectRatio);
  void Render(ID3D11DeviceContext *deviceContext);
private:
  bool InitializeShader(ID3D11Device *device);
  bool InitializeConstantBuffer(ID3D11Device *device, float aspectRatio);
  void Shutdown();
  ID3D11VertexShader *vertexShader_;
  ID3D11PixelShader *pixelShader_;
  ID3D11InputLayout *vertexLayout_;
  ID3D11Buffer *cbImmutable_;
  ID3D11Buffer *cbPerFrame_;
  ID3D11Buffer *cbPerObject_;
  class ImmutableBuffer
  {
  public:
    DirectX::XMFLOAT4X4 projection_;
  };
  class PerFrameBuffer
  {
  public:
    DirectX::XMFLOAT4X4 worldToView_;
  };
  class PerObjectBuffer
  {
  public:
    DirectX::XMFLOAT4X4 modelToWorld_;
  };
};
}