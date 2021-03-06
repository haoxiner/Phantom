#include "InputHandler.h"

phtm::InputHandler::InputHandler()
  :directInput_(nullptr), inputDevice_(nullptr)
{
}

bool phtm::InputHandler::Initialize(HINSTANCE hInstance, HWND hWnd)
{
  HRESULT hr = DirectInput8Create(
    hInstance,
    DIRECTINPUT_VERSION,
    IID_IDirectInput8,
    (void**)&directInput_,
    NULL);
  if (FAILED(hr))
    return false;
  hr = directInput_->CreateDevice(
    GUID_SysKeyboard,
    &inputDevice_,
    NULL);
  if (FAILED(hr))
    return false;
  hr = inputDevice_->SetDataFormat(&c_dfDIKeyboard);
  if (FAILED(hr))
    return false;
  hr = inputDevice_->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
  if (FAILED(hr))
    return false;
  hr = inputDevice_->Acquire();
  if (FAILED(hr))
    return false;
  return true;
}

void phtm::InputHandler::Update()
{
  HRESULT hr = inputDevice_->GetDeviceState(
    sizeof(input_.keyDown_),
    (LPVOID)&input_.keyDown_);
  if (FAILED(hr))
  {
    if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
      inputDevice_->Acquire();
  }
}

void phtm::InputHandler::Close()
{
  if (inputDevice_) inputDevice_->Release();
  if (directInput_) directInput_->Release();
}
