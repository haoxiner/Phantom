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
  bool Initialize(ID3D11Device *device);
  void Render(ID3D11DeviceContext *context);
private:
  bool InitializeShader(ID3D11Device *device);
  bool InitializeConstantBuffer(ID3D11Device *device);
  ID3D11VertexShader *vertexShader_;
  ID3D11PixelShader *pixelShader_;
  ID3D11InputLayout *vertexLayout_;
  ID3D11Buffer *cbChangeOnResize_;
  ID3D11Buffer *cbChangeFrequently_;
  class ChangeOnResize
  {
  public:
    DirectX::XMFLOAT4X4 projection_;
  };
  class ChangeFrequently
  {
  public:
    DirectX::XMFLOAT4X4 modelToWorld_;
    DirectX::XMFLOAT4X4 worldToView_;
  };
};
}