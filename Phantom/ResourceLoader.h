#pragma once
#include "RawModel.h"
#include "Graphics.h"
#include "Vertex.h"
#include <string>
#include <vector>

namespace phtm
{
class ResourceLoader
{
public:
  ResourceLoader();
  void Initialize(Graphics *graphics);
  void CleanUp();
  void LoadRMD(
    RawModel &rawModel,
    const std::string &filename);
  void LoadRawModel(
    RawModel &rawModel,
    const std::vector<Vertex> &vertices,
    const std::vector<int> &indices);
private:
  Graphics *graphics_;
};
}