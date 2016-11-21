#pragma once
namespace phtm
{
class Component
{
public:
  Component() : isActive_(false) {};
  virtual ~Component() {};
  virtual void SetActive(bool active) { isActive_ = active; }
  virtual bool IsActive() { return isActive_; }
protected:
  bool isActive_;
};
}