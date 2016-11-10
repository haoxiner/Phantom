#pragma once
#include "System.h"
#include "Graphics.h"
#include "SimpleRenderer.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>
#include <string>

namespace phtm
{
class ChangeOnResize
{
public:
  DirectX::XMFLOAT4X4 modelToWorld;
  DirectX::XMFLOAT4X4 view_;
  DirectX::XMFLOAT4X4 projection_;
};
class RenderingSystem : public System
{
public:
  RenderingSystem(Graphics *graphics, int screenWidth, int screenHeight);
  virtual ~RenderingSystem() {}
  virtual bool Initialize();
  virtual void Update(Message &message);
  virtual void CleanUp();
private:
  bool CreateSimpleVertexShader(ID3D11Device *d3dDevice);
  bool CreateSimplePixelShader(ID3D11Device *d3dDevice);
  Graphics *graphics_;
  SimpleRenderer simpleRenderer_;
  std::vector<ID3D11VertexShader*> vertexShaders_;
  std::vector<ID3D11PixelShader*> pixelShaders_;
  std::vector<ID3D11InputLayout*> inputLayouts_;
  std::vector<ID3D11Buffer*> constantBuffers_;

private:
  ChangeOnResize changeOnResize;
};
}