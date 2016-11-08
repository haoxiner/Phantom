#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

int main()
{
  Assimp::Importer importer;
  auto scene = importer.ReadFile("", aiProcessPreset_TargetRealtime_Fast);
  return 0;
}