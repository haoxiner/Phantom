#pragma once
#include "RawModel.h"
#include "Camera.h"
#include <d3d11.h>

namespace phtm
{
class SimpleRenderer
{
public:
  SimpleRenderer() {}
  ~SimpleRenderer() {}
  bool Initialize(
    ID3D11VertexShader *vertexShader,
    ID3D11InputLayout *vertexLayout,
    ID3D11PixelShader *pixelShader,
    ID3D11Buffer *constBuffer);
  void Render(ID3D11DeviceContext *context, RawModel &rawModel, Camera &camera);
private:
  ID3D11VertexShader *vertexShader_;
  ID3D11PixelShader *pixelShader_;
  ID3D11InputLayout *vertexLayout_;
  ID3D11Buffer *constBuffer_;
};
}