#include "Input.h"

phtm::Input::Input()
  :directInput_(nullptr), inputDevice_(nullptr)
{
}

bool phtm::Input::Quit()
{
  return keyDown_[DIK_Q];
}

float phtm::Input::LeftHorizontalAxisX()
{
  float value = 0.0f;
  if (keyDown_[DIK_D])
  {
    value += 1.0f;
  }
  if (keyDown_[DIK_A])
  {
    value -= 1.0f;
  }
  return value;
}

float phtm::Input::LeftHorizontalAxisY()
{
  float value = 0.0f;
  if (keyDown_[DIK_W])
  {
    value += 1.0f;
  }
  if (keyDown_[DIK_S])
  {
    value -= 1.0f;
  }
  return value;
}

bool phtm::Input::Initialize(HINSTANCE hInstance, HWND hWnd)
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

void phtm::Input::Update()
{
  HRESULT hr = inputDevice_->GetDeviceState(
    sizeof(keyDown_),
    (LPVOID)&keyDown_);
  if (FAILED(hr))
  {
    if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
      inputDevice_->Acquire();
  }
}

void phtm::Input::Close()
{
  if (inputDevice_) inputDevice_->Release();
  if (directInput_) directInput_->Release();
}
