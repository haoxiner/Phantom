#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

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

void CalcMaxBonesPerVertex(const aiScene *scene)
{
  if (scene)
  {
    std::cout << "Number Of Meshes: " << scene->mNumMeshes << std::endl;
    std::cout << "Number Of Textures: " << scene->mNumTextures << std::endl;
    std::cout << "Number Of Animations: " << scene->mNumAnimations << std::endl;

    std::cout << "Bones: " << scene->mRootNode->mNumChildren << std::endl;
    std::cout << "Meshes: " << scene->mRootNode->mNumMeshes << std::endl;
    for (int i = 0; i < scene->mNumMeshes; i++)
    {
      auto mesh = scene->mMeshes[i];
      std::cout << mesh->mName.C_Str() << std::endl;
      std::map<int, int> total;
      std::cout << "Number Of Bones: " << mesh->mNumBones << std::endl;
      for (int j = 0; j < mesh->mNumBones; j++)
      {
        auto bone = mesh->mBones[j];
        for (int k = 0; k < bone->mNumWeights; k++)
        {
          if (total.find(bone->mWeights[k].mVertexId) != total.end())
          {
            total[bone->mWeights[k].mVertexId] += 1;
          }
          else
          {
            total[bone->mWeights[k].mVertexId] = 1;
          }
        }
      }
      int max = -1000;
      for (auto p : total)
      {
        max = std::max(max, p.second);
      }
      std::cout << "max bones: " << max << std::endl;
      std::cout << "================" << std::endl;
    }
  }
}

int main()
{
	Assimp::Importer importer;
	auto scene = importer.ReadFile(
		"D:/GameDev/FinalResource/man.fbx", aiProcessPreset_TargetRealtime_Fast);
	std::cerr << /*scene->mNumMeshes*/2 << std::endl;
	int numOfVertices = 0;
	int numOfFaces = 0;
	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		numOfVertices += scene->mMeshes[i]->mNumVertices;
		numOfFaces += scene->mMeshes[i]->mNumFaces;
	}

	std::ofstream output("D:/GameDev/Resources/proto.rmd", std::ios::binary);
	output.write((char*)&numOfVertices, sizeof(int));
	output.write((char*)&numOfFaces, sizeof(int));
  std::cout << "Faces: " << numOfFaces << std::endl;
	std::cout << "Processing..." << std::endl;
	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		auto mesh = scene->mMeshes[i];
		for (size_t j = 0; j < mesh->mNumVertices; j++)
		{
			auto v = mesh->mVertices[j];
			auto n = mesh->mNormals[j];
			auto texCoord = mesh->mTextureCoords[0][j];
			auto tangent = mesh->mTangents[j];
			Vertex vertex;
			vertex.x = v.x; vertex.y = v.y; vertex.z = v.z;
			vertex.nx = n.x; vertex.ny = n.y; vertex.nz = n.z;
			vertex.s = texCoord.x; vertex.t = texCoord.y;
			vertex.tx = tangent.x; vertex.ty = tangent.y; vertex.tz = tangent.z;
			output.write((char*)&vertex, sizeof(Vertex));
		}
	}
  int maxId = -1;
  int indicesBase = 0;
  for (int i = 0; i < scene->mNumMeshes; i++)
  {
    auto mesh = scene->mMeshes[i];
    for (size_t j = 0; j < mesh->mNumFaces; j++)
    {
      auto face = mesh->mFaces[j];
      for (size_t k = 0; k < 3; k++)
      {
        
        int index = face.mIndices[k] + indicesBase;
        maxId = std::max(index, maxId);
        output.write((char*)&index, sizeof(int));
      }
    }
    indicesBase += mesh->mNumVertices;
  }
  std::cerr << maxId << "/" << numOfVertices << std::endl;
  std::cerr << indicesBase << std::endl;
	std::cout << "Finished" << std::endl;
	output.close();
	return 0;
}