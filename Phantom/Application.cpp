#include "Application.h"
#include <sstream>

phtm::Application::Application()
  :hInstance_(GetModuleHandle(NULL)), applicationName_(L"Phantom"), running_(false)
{
}

void phtm::Application::Run()
{
  if (!Initialize())
  {
    Shutdown();
    return;
  }
  StartGame();
  unsigned long startTick = 0;
  unsigned long endTick = 0;
  int frame = 0;
  float elapsedTime = 0.0f;
  float deltaTime = 0.0f;// seconds
  MSG msg = {0};
  while (running_ && msg.message != WM_QUIT)
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
    {
      startTick = GetTickCount();
      // update input
      input_.Update();
      // do game loop
      UpdateGame(deltaTime);

      endTick = GetTickCount();
      if (endTick < startTick)
      {
        endTick = startTick;
      }
      deltaTime = 0.001f * static_cast<float>(endTick - startTick);

      /*
      float timeCap = 1.0f / 60.0f;
      if (deltaTime < timeCap)
      {
        Sleep(static_cast<unsigned long>(timeCap*1000 - deltaTime*1000));
        deltaTime = timeCap;
      }
      */
      frame++;
      elapsedTime += deltaTime;
      if (elapsedTime > 1.0f)
      {
        float fps = static_cast<float>(frame) / elapsedTime;
        std::wostringstream oss;
        oss.precision(6);
        oss << fps;
        SetWindowText(hWnd_, oss.str().c_str());
        frame = 0;
        elapsedTime = 0.0f;
      }
    }
  }
  EndGame();
  Shutdown();
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
  if (!input_.Initialize(hInstance_, hWnd_))
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
  switch (message)
  {
  case WM_CLOSE:
    PostQuitMessage(0);
    return 0;
  break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
}

bool phtm::Application::InitializeWindow()
{
  WNDCLASSEX wc;
  ZeroMemory(&wc, sizeof(wc));
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc = WindowProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance_;
  wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
  wc.hIconSm = wc.hIcon;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = applicationName_;
  wc.cbSize = sizeof(WNDCLASSEX);
  RegisterClassEx(&wc);

  int screenWidth = GetSystemMetrics(SM_CXSCREEN);
  int screenHeight = GetSystemMetrics(SM_CYSCREEN);

  // Full screen mode is implemented in DirectX, this block has been commented.
  // To Full Screen Mode
  /*
  DEVMODE dmScreenSettings;
  memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
  dmScreenSettings.dmSize = sizeof(dmScreenSettings);
  dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
  dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
  dmScreenSettings.dmBitsPerPel = 32;
  dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
  ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
  */

  int posX = 0, posY = 0;

  // Create the window with the screen settings and get the handle to it.
  hWnd_ = CreateWindowEx(WS_EX_APPWINDOW, applicationName_, applicationName_,
    WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP | WS_OVERLAPPEDWINDOW,
    posX, posY, screenWidth, screenHeight, NULL, NULL, hInstance_, NULL);
  // Bring the window up on the screen and set it as main focus.
  ShowWindow(hWnd_, SW_SHOW);
  SetForegroundWindow(hWnd_);
  SetFocus(hWnd_);
  // Hide the mouse cursor.
  ShowCursor(false);
  return true;
}
