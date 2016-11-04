#include "Display.h"

static LRESULT CALLBACK WindowProc(HWND hWnd,
  UINT message,
  WPARAM wParam,
  LPARAM lParam);

bool phtm::Display::Initialize()
{
  WNDCLASSEX wc;
  DEVMODE dmScreenSettings;
  int posX = 0;
  int posY = 0;
  hInstance_ = GetModuleHandle(NULL);
  applicationName_ = L"Phantom";
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

bool phtm::Display::IsRunning()
{
  return true;
}

void phtm::Display::Update()
{
  static MSG msg;
  if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  // sort through and find what code to run for the message given
  switch (message)
  {
  case WM_KEYDOWN:
  {

  }
  break;
  case WM_DESTROY:
  {
    PostQuitMessage(0);
    return 0;
  }
  break;
  }

  // Handle any messages the switch statement didn't
  return DefWindowProc(hWnd, message, wParam, lParam);
}