#pragma once
#include <d3d11.h>

namespace phtm
{
class SimpleShader
{
public:
  SimpleShader() {}
  ~SimpleShader() {}
  void Initialize(ID3D11Device *d3dDevice);
  void Render(ID3D11DeviceContext *context, ID3D11Buffer *vertexBuffer, int stride, int offset);
private:
  ID3D11VertexShader *vertexShader_;
  ID3D11PixelShader *pixelShader_;
  ID3D11InputLayout *vertexLayout_;
};
}