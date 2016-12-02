#pragma once
#include "System.h"
#include "Graphics.h"
#include "RawModel.h"
#include "DeferredBuffers.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>
#include <string>

namespace phtm
{
class ChangeOnResize
{
public:
  DirectX::XMFLOAT4X4 projection_;
};
class ChangeEveryFrame
{
public:
  DirectX::XMFLOAT4X4 modelToWorld;
  DirectX::XMFLOAT4X4 view_;
};
class RenderingSystem : public System
{
public:
  RenderingSystem();
  virtual ~RenderingSystem() {}
  bool Initialize(Graphics *graphics, int screenWidth, int screenHeight);
  virtual void Update(Message &message);
  virtual void CleanUp();
private:
  bool CreateSimpleVertexShader(ID3D11Device *d3dDevice);
  bool CreateSimplePixelShader(ID3D11Device *d3dDevice);
  void SimpleRender(ID3D11DeviceContext *context, RawModel &rawModel, Camera &camera);
  Graphics *graphics_;
  std::vector<ID3D11VertexShader*> vertexShaders_;
  std::vector<ID3D11PixelShader*> pixelShaders_;
  std::vector<ID3D11InputLayout*> inputLayouts_;
  std::vector<ID3D11Buffer*> constantBuffers_;
private:
  ChangeOnResize changeOnResize;
  ChangeEveryFrame changeEveryFrame;

  DeferredBuffers deferredBuffers_;
};
}