#pragma once

namespace phtm
{
class Message;
class Entity
{
public:
  Entity() {}
  virtual ~Entity();
  virtual void Update(Message &message) = 0;
private:

};
}