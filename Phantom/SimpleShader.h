#pragma once
#include "RawModel.h"
#include <d3d11.h>

namespace phtm
{
class SimpleShader
{
public:
  SimpleShader() {}
  ~SimpleShader() {}
  bool Initialize(ID3D11Device *d3dDevice);
  void Render(ID3D11DeviceContext *context, RawModel &rawModel);
private:
  ID3D11VertexShader *vertexShader_;
  ID3D11PixelShader *pixelShader_;
  ID3D11InputLayout *vertexLayout_;
};
}