#include "Application.h"

phtm::Application *phtm::Application::applicationInstance_ = new phtm::Application();
phtm::Application *application = phtm::Application::GetInstance();

phtm::Application *phtm::Application::GetInstance()
{
  return applicationInstance_;
}

phtm::Application::Application()
  :hInstance_(GetModuleHandle(NULL)), applicationName_(L"Phantom")
{
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
      if (msg.message == WM_QUIT)
      {
        break;
      }
    }
    graphics_.Update();
  }
  Shutdown();
}

LRESULT phtm::Application::HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_KEYDOWN:
  {
    PostQuitMessage(0);
    //m_Input->KeyDown((unsigned int)wparam);
    return 0;
  }
  break;
  case WM_KEYUP:
  {
    //m_Input->KeyUp((unsigned int)wparam);
    return 0;
  }
  break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
}

bool phtm::Application::Initialize()
{
  if (!InitializeWindow())
  {
    return false;
  }
  if (!graphics_.Initialize(hWnd_))
  {
    return false;
  }
  return true;
}

void phtm::Application::Shutdown()
{
  graphics_.Shutdown();
}

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  return application->HandleMessage(hWnd, message, wParam, lParam);
}

bool phtm::Application::InitializeWindow()
{
  WNDCLASSEX wc;
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc = WindowProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance_;
  wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
  wc.hIconSm = wc.hIcon;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  //wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = applicationName_;
  wc.cbSize = sizeof(WNDCLASSEX);
  RegisterClassEx(&wc);

  int screenWidth = GetSystemMetrics(SM_CXSCREEN);
  int screenHeight = GetSystemMetrics(SM_CYSCREEN);
  DEVMODE dmScreenSettings;
  memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
  dmScreenSettings.dmSize = sizeof(dmScreenSettings);
  dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
  dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
  dmScreenSettings.dmBitsPerPel = 32;
  dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
  // Change the display settings to full screen.
  ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
  int posX = 0, posY = 0;
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
