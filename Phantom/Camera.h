#pragma once
#include <DirectXMath.h>

namespace phtm
{
class Message;
class Camera
{
public:
  Camera();
  void Update(Message &message);
  DirectX::XMFLOAT4X4 view_;
private:
  float distance_;
  float roll_, pitch_, yaw_;

  float theta_, phi_;
  float radius_;
};
}