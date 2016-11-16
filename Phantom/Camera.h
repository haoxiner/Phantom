#pragma once
#include <DirectXMath.h>

namespace phtm
{
class Player;
class Message;
class Camera
{
public:
  Camera();
  void Update(Message &message);
  void SetPlayer(Player *player) { player_ = player; }
  DirectX::XMFLOAT4X4 view_;
private:
  Player *player_;
  float distance_;
  float roll_, pitch_, yaw_;
};
}