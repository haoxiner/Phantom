#include "SimpleRenderer.h"
#include "Vertex.h"

bool phtm::SimpleRenderer::Initialize(
  ID3D11VertexShader *vertexShader,
  ID3D11InputLayout *vertexLayout,
  ID3D11PixelShader *pixelShader,
  ID3D11Buffer *constBuffer)
{
  vertexShader_ = vertexShader;
  vertexLayout_ = vertexLayout;
  pixelShader_ = pixelShader;
  constBuffer_ = constBuffer;
  return true;
}

void phtm::SimpleRenderer::Render(ID3D11DeviceContext *context, RawModel &rawModel, Camera &camera)
{
  context->UpdateSubresource(constBuffer_, 0, nullptr, &camera, 0, 0);

  context->IASetInputLayout(vertexLayout_);
  UINT stride1 = sizeof(Vertex);
  UINT offset1 = 0;
  context->IASetVertexBuffers(0, 1, &rawModel.vertexBuffer_, &stride1, &offset1);
  context->IASetIndexBuffer(rawModel.indexBuffer_, DXGI_FORMAT_R32_UINT, 0);
  context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  context->VSSetShader(vertexShader_, nullptr, 0);
  context->PSSetShader(pixelShader_, nullptr, 0);
  context->VSSetConstantBuffers(0, 1, &constBuffer_);
  context->DrawIndexed(rawModel.indexCount_, 0, 0);
};

