#pragma once

namespace phtm
{
class Input;
class Camera;
class Player;
class ComponentCollection;
class Message
{
public:
  Message();
  ~Message();
  float deltaTimeInSeconds_;
  ComponentCollection *componentCollection_;
  Input *input_;
  Camera *camera_;
  Player *player_;
private:
};
}