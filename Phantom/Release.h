#pragma once
namespace phtm
{
template<class T>
inline void Release(T *t)
{
  if (t != nullptr)
  {
    t->Release();
  }
}
}