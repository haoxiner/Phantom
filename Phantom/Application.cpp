#include "Application.h"

phtm::Application::Application()
  :display_(nullptr), graphics_(nullptr)
{
}

void phtm::Application::Run()
{
  if (!Initialize())
  {
    Close();
    return;
  }
  while (true)
  {
    display_->Update();
  }
  Close();
}

bool phtm::Application::Initialize()
{
  display_ = new Display();
  if (!display_ || !display_->Initialize())
  {
    return false;
  }
  return true;
}

void phtm::Application::Close()
{
  delete display_;
  delete graphics_;
}
