#include "ResourceLoader.h"
#include <fstream>

phtm::ResourceLoader::ResourceLoader()
{
}

void phtm::ResourceLoader::Initialize(Graphics *graphics)
{
  graphics_ = graphics;
}

void phtm::ResourceLoader::CleanUp()
{
  graphics_ = nullptr;
}

void phtm::ResourceLoader::LoadRMD(RawModel &rawModel, const std::string &filename)
{
  auto d3dDevice = graphics_->GetD3DDevice();
  std::ifstream rmd(filename, std::ios::binary);
  int numOfVertices, numOfFaces;
  rmd.read((char*)&numOfVertices, sizeof(int));
  rmd.read((char*)&numOfFaces, sizeof(int));
  rawModel.indexCount_ = numOfFaces * 3;

  std::vector<Vertex> vertices;
  vertices.reserve(numOfVertices);
  vertices.resize(numOfVertices);
  rmd.read((char*)&vertices[0], numOfVertices * sizeof(Vertex));
  for (auto &vertex : vertices)
  {
    auto simdPosition = DirectX::XMLoadFloat3(&vertex.position_);
    DirectX::XMStoreFloat3(
      &vertex.position_,
      DirectX::XMVectorScale(simdPosition, 0.01f));
  }
  
  std::vector<int> indices;
  indices.reserve(rawModel.indexCount_);
  indices.resize(rawModel.indexCount_);
  rmd.read((char*)&indices[0], rawModel.indexCount_ * sizeof(int));
  rmd.close();

  LoadRawModel(rawModel, vertices, indices);
}

void phtm::ResourceLoader::LoadRawModel(
  RawModel &rawModel,
  const std::vector<Vertex> &vertices,
  const std::vector<int> &indices)
{
  rawModel.indexCount_ = indices.size();
  auto d3dDevice = graphics_->GetD3DDevice();
  // submit to GPU
  D3D11_BUFFER_DESC bufferDesc;
  ZeroMemory(&bufferDesc, sizeof(bufferDesc));
  bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
  bufferDesc.ByteWidth = static_cast<UINT>(sizeof(Vertex) * vertices.size());
  bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  D3D11_SUBRESOURCE_DATA initData;
  ZeroMemory(&initData, sizeof(initData));
  initData.pSysMem = &vertices[0];
  HRESULT hr = d3dDevice->CreateBuffer(
    &bufferDesc, &initData, &rawModel.vertexBuffer_);
  if (FAILED(hr))
  {
    return;
  }
  D3D11_BUFFER_DESC indexBufferDesc;
  ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
  indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
  indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
  indexBufferDesc.ByteWidth = static_cast<UINT>(sizeof(int) * indices.size());
  D3D11_SUBRESOURCE_DATA indexData;
  ZeroMemory(&indexData, sizeof(indexData));
  indexData.pSysMem = &indices[0];
  hr = d3dDevice->CreateBuffer(&indexBufferDesc, &indexData, &rawModel.indexBuffer_);
  if (FAILED(hr))
  {
    return;
  }
}
