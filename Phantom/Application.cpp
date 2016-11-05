#include "Application.h"

phtm::Application *phtm::Application::applicationInstance_ = new phtm::Application();

phtm::Application::Application()
  :hInstance_(GetModuleHandle(NULL)), applicationName_(L"Phantom")
{
}

phtm::Application *phtm::Application::GetInstance()
{
  return applicationInstance_;
}

void phtm::Application::Run()
{
  if (!Initialize())
  {
    Shutdown();
    return;
  }
  MSG msg;
  while (true)
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    if (msg.message == WM_QUIT)
    {
      Shutdown();
      break;
    }
    graphics_.Update();
  }
  Shutdown();
}

bool phtm::Application::Initialize()
{
  if (!InitializeWindow())
  {
    return false;
  }
  if (!graphics_.Initialize())
  {
    return false;
  }
  return true;
}

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_KEYDOWN:
  {

  }
  break;
  case WM_CLOSE:
  {
    PostQuitMessage(0);
    return 0;
  }
  break;
  case WM_DESTROY:
  {
    PostQuitMessage(0);
    return 0;
  }
  break;
  }
  return DefWindowProc(hWnd, message, wParam, lParam);
}

bool phtm::Application::InitializeWindow()
{
  WNDCLASSEX wc;
  DEVMODE dmScreenSettings;
  int posX = 0;
  int posY = 0;
  
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc = WindowProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance_;
  wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
  wc.hIconSm = wc.hIcon;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = applicationName_;
  wc.cbSize = sizeof(WNDCLASSEX);

  RegisterClassEx(&wc);
  int screenWidth = GetSystemMetrics(SM_CXSCREEN);
  int screenHeight = GetSystemMetrics(SM_CYSCREEN);

  memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
  dmScreenSettings.dmSize = sizeof(dmScreenSettings);
  dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
  dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
  dmScreenSettings.dmBitsPerPel = 32;
  dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

  // Change the display settings to full screen.
  ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

  // Create the window with the screen settings and get the handle to it.
  hWnd_ = CreateWindowEx(WS_EX_APPWINDOW, applicationName_, applicationName_,
    WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
    posX, posY, screenWidth, screenHeight, NULL, NULL, hInstance_, NULL);

  // Bring the window up on the screen and set it as main focus.
  ShowWindow(hWnd_, SW_SHOW);
  SetForegroundWindow(hWnd_);
  SetFocus(hWnd_);

  // Hide the mouse cursor.
  ShowCursor(false);
  return true;
}

LRESULT phtm::Application::MessageHandler(HWND, UINT, WPARAM, LPARAM)
{
  return LRESULT();
}

void phtm::Application::Shutdown()
{
}