/* FILE NAME   : winmsg.cpp
 * PROGRAMMER  : TT6
 * LAST UPDATE : 19.12.2021
 * PURPOSE     : Message crackers.
 */

#include "win.h"

/* Project namespace */
namespace tart
{
  /* Window message message handle function.
   * ARGUMENTS:
   *   - window descriptor
   *       HWND hWnd;
   *   - message number
   *       UINT Msg;
   *   - word parameter
   *       WPARAM wParam;
   *   - long parameter
   *       LPARAM lParam;
   * RETURNS:
   *   (LRESULT) depends on a message.
   */
  LRESULT CALLBACK win::WinFunc( HWND hWnd, UINT Msg,
                                 WPARAM wParam, LPARAM lParam )
  {
    win *Win;
    HDC hDC;
    PAINTSTRUCT ps;

    switch (Msg)
    {
    case WM_GETMINMAXINFO:
      ((MINMAXINFO *)lParam)->ptMaxTrackSize.y =
        GetSystemMetrics(SM_CYMAXTRACK) +
        GetSystemMetrics(SM_CYCAPTION) +
        GetSystemMetrics(SM_CYMENU) +
        GetSystemMetrics(SM_CYBORDER) * 2;
      return 0;

    case WM_CREATE:
      SetWindowLongPtr(hWnd, 0, (UINT_PTR)((CREATESTRUCT *)lParam)->lpCreateParams);
      Win = reinterpret_cast<win *>((UINT_PTR)((CREATESTRUCT *)lParam)->lpCreateParams);
      Win->hWnd = hWnd;
    default:
      Win = reinterpret_cast<win *>(GetWindowLongPtr(hWnd, 0));
      if (Win != nullptr)
        switch (Msg)
        {
        case WM_CREATE:
          Win->hWnd = hWnd;
          return Win->OnCreate((CREATESTRUCT *)lParam) ? 0 : -1;

        case WM_SIZE:
          Win->OnSize(wParam, LOWORD(lParam), HIWORD(lParam));
          return 0;

        case WM_ERASEBKGND:
          return (LRESULT)Win->OnEraseBackground((HDC)wParam);

        case WM_PAINT:
          hDC = BeginPaint(hWnd, &ps);
          Win->OnPaint(hDC, &ps);
          EndPaint(hWnd, &ps);
          return 0;

        case WM_TIMER:
          Win->OnTimer((UINT)wParam);
          return 0;

        case WM_MOUSEWHEEL:
          Win->OnMouseWheel((INT)(SHORT)LOWORD(lParam),
                            (INT)(SHORT)HIWORD(lParam),
                            (INT)(SHORT)HIWORD(wParam),
                            (UINT)(SHORT)LOWORD(wParam));
          return 0;

        case WM_LBUTTONDOWN:
          SetCapture(hWnd);
          return 0;

        case WM_LBUTTONUP:
          ReleaseCapture();
          return 0;
      
        case WM_DESTROY:
          Win->OnDestroy();
          PostQuitMessage(30);
          return 0;
        }
      break;
    case WM_KEYDOWN:
      // Close the window if 'Esc' button is tapped
      if (wParam == VK_ESCAPE)
      {
        SendMessage(hWnd, WM_CLOSE, 0, 0);
        return 0;
      }
      if (wParam == 'f')
      {
        FlipFullScreen(hWnd);
        return 0;
      }
    }
    return DefWindowProc(hWnd, Msg, wParam, lParam);
  } /* End of 'WinFunc' function */

  /* Message loop handle.
   * ARGUMENTS: None.
   * RETURNS:
   *   (WPARAM) Code 'WM_QUIT' returning from wParam
   */
  WPARAM win::Run( VOID )
  {
    MSG msg;

    // Message loop
    while (TRUE)
    {
      if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        if (msg.message == WM_QUIT)
          break;
        else
        {
          // Displatch message to window:
          TranslateMessage(&msg);
          DispatchMessage(&msg);
        }
      else
        Idle();
    }

    return msg.wParam;
  } /* End of 'win::Run' function */

  /* Flip full screen function.
   * ARGUMENTS:
   *   - window handle:
   *       HWND hWnd;
   * RETURNS: None.
   */
  VOID win::FlipFullScreen( HWND hWnd )
  {
    static BOOL IsFullScreen = FALSE; /* store current mode */
    static RECT SaveRC;               /* save old window size */

    if (!IsFullScreen)
    {
      HMONITOR hMon;
      MONITORINFOEX moninfo;
      RECT rc;

      IsFullScreen = TRUE;

      /* Save old window size and position */
      GetWindowRect(hWnd, &SaveRC);

      /* Get closest monitor */
      hMon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

      /* Get monitor information */
      moninfo.cbSize = sizeof(moninfo);
      GetMonitorInfo(hMon, (MONITORINFO*)&moninfo);

      rc = moninfo.rcMonitor;
      AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);

      /* Expand window to full screen */
      SetWindowPos(hWnd, HWND_TOPMOST,
        rc.left, rc.top,
        rc.right - rc.left, rc.bottom - rc.top,
        SWP_NOOWNERZORDER);
    }
    else
    {
      IsFullScreen = FALSE;

      /* Restore window size and position */
      SetWindowPos(hWnd, HWND_NOTOPMOST,
        SaveRC.left, SaveRC.top,
        SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top,
        SWP_NOOWNERZORDER);
    }
  } /* End of 'FlipFullScreen' function */

  /* WM_CREATE window message handle function.
   * ARGUMENTS:
   *   - structure with creation data:
   *       CREATESTRUCT *CS;
   * RETURNS:
   *   (BOOL) TRUE to continue creation window, FALSE to terminate.
   */
  BOOL win::OnCreate( CREATESTRUCT *CS )
  {
    // setup InitTimer:
    SetTimer(hWnd, 100, 1, nullptr);
    return TRUE;
  } /* End of 'win::OnCreate' function */

  /* WM_DESTROY window message handle function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID win::OnDestroy( VOID )
  {
    if (IsInit)
    {
      KillTimer(hWnd, 101);
      Close();
    }
    else
      KillTimer(hWnd, 100);
  } /* End of 'win::OnDestroy' function */

  /* WM_SIZE window message handle function.
   * ARGUMENTS:
   *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
   *       UINT State;
   *   - new width and height of client area:
   *       INT W, H;
   * RETURNS: None.
   */
  VOID win::OnSize( UINT State, INT W, INT H )
  {
    this->W = W;
    this->H = H;
    if (IsInit)
      Resize();
} /* End of 'win::OnSize' function */

  /* WM_ERASEBKGND window message handle function.
   * ARGUMENTS:
   *   - device context of client area:
   *       HDC hDC;
   * RETURNS:
   *   (BOOL) TRUE if background is erased, FALSE otherwise.
   */
  BOOL win::OnEraseBackground( HDC hDC )
  {
    if (IsInit)
      Erase(hDC);
    return TRUE;
  } /* End of 'win::OnEraseBkgnd' function */

  /* WM_PAINT window message handle function.
   * ARGUMENTS:
   *   - window device context:
   *       HDC hDC;
   *   - paint message structure pointer:
   *       PAINTSTRUCT *PS;
   * RETURNS: None.
   */
  VOID win::OnPaint( HDC hDC, PAINTSTRUCT *PS )
  {
    if (IsInit)
      Paint(hDC);
  } /* End of 'win::OnPaint' function */ 

  /* WM_ACTIVATE window message handle function.
   * ARGUMENTS:
   *   - reason (WA_CLICKACTIVE, WA_ACTIVE or WA_INACTIVE):
   *       UINT Reason;
   *   - handle of active window:
   *       HWND hWndActDeact;
   *   - minimized flag:
   *       BOOL IsMinimized;
   * RETURNS: None.
   */
  VOID win::OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized )
  {
    IsActive = Reason == WA_CLICKACTIVE || Reason == WA_ACTIVE;
    if (IsInit)
      Activate();
  } /* End of 'win::OnActivate' function */

  /* WM_TIMER window message handle function.
   * ARGUMENTS:
   *   - specified the timer identifier.
   *       INT Id;
   * RETURNS: None.
   */
  VOID win::OnTimer( INT Id ) 
  {
    if (!IsInit)
    {
      // kill InitTimer:
      KillTimer(hWnd, 100);
      // setup RefreshTimer:
      SetTimer(hWnd, 101, 1, nullptr);

      IsInit = TRUE;

      // call callbacks
      Init();
      Resize();
      Timer();
      InvalidateRect(hWnd, nullptr, FALSE);
    }
    else
      Timer();
  } /* End of 'win::OnTimer' function */

  /* WM_MOUSEWHEEL window message handle function.
   * ARGUMENTS:
   *   - mouse window position:
   *       INT X, Y;
   *   - mouse wheel relative delta value:
   *       INT Z;
   *   - mouse keys bits (see MK_*** bits constants):
   *       UINT Keys;
   * RETURNS: None.
   */
  VOID win::OnMouseWheel( INT X, INT Y, INT Z, UINT Keys )
  {
    MouseWheel += Z;
  } /* End of 'win::OnMouseWheel' function */

  /* WM_CLOSE window message handle function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID win::OnClose( VOID )
  {
    Close();
  } /* End of 'win::OnClose' function */
} /* End of 'tart' namespace */

/* END OF 'winmsg.cpp' FILE */
