#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <fstream>

class Vertex
{
public:
  float x, y, z;
  float nx, ny, nz;
  float s, t;
  float tx, ty, tz;
private:

};

void GenerateQuad()
{
  int numOfVertices = 4, numOfFaces = 2;
  std::ofstream output("D:/GameDev/Resources/quad.rmd", std::ios::binary);
  output.write((char*)&numOfVertices, sizeof(int));
  output.write((char*)&numOfFaces, sizeof(int));

  float vertices[] =
  {
    // top left
    -0.5f,0.5f,0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    // bottom left
    -0.5f,-0.5f,0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    // top right
    0.5f,0.5f,0.5f,   0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    // bottom right
    0.5f,-0.5f,0.5f,  0.0f, 0.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
  };
  int indices[] =
  {
    0,2,3,
    0,3,1
  };

  std::cout << "Processing..." << std::endl;
  output.write((char*)&vertices, sizeof(vertices));
  output.write((char*)&indices, sizeof(indices));
  output.close();
}

int main()
{
  GenerateQuad();
  return 0;

  Assimp::Importer importer;
  auto scene = importer.ReadFile("D:/GameDev/Resources/Paladin_w_Prop_J_Nordstrom.fbx", aiProcessPreset_TargetRealtime_Fast);
  auto mesh = scene->mMeshes[0];

  std::ofstream output("D:/GameDev/Resources/knight.rmd", std::ios::binary);
  output.write((char*)&mesh->mNumVertices, sizeof(int));
  output.write((char*)&mesh->mNumFaces, sizeof(int));
  std::cout << "Processing..." << std::endl;
  for (size_t i = 0; i < mesh->mNumVertices; i++)
  {
    
    auto v = mesh->mVertices[i];
    auto n = mesh->mNormals[i];
    auto texCoord = mesh->mTextureCoords[0][i];
    auto tangent = mesh->mTangents[i];
    Vertex vertex;
    vertex.x = v.x; vertex.y = v.y; vertex.z = v.z;
    vertex.nx = n.x; vertex.ny = n.y; vertex.nz = n.z;
    vertex.s = texCoord.x; vertex.t = texCoord.y;
    vertex.tx = tangent.x; vertex.ty = tangent.y; vertex.tz = tangent.z;
    output.write((char*)&vertex, sizeof(Vertex));
  }
  for (size_t i = 0; i < mesh->mNumFaces; i++)
  {
    auto face = mesh->mFaces[i];
    for (size_t j = 0; j < 3; j++)
    {
      output.write((char*)&face.mIndices[j], sizeof(int));
    }
  }
  std::cout << "Finished" << std::endl;
  output.close();
  return 0;
}