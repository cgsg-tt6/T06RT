/* FILE NAME   : win.cpp
 * PROGRAMMER  : TT6
 * LAST UPDATE : 26.08.2021
 * PURPOSE     : Window making function.
 */

#include "win.h"

#define WND_CLASS_NAME "CGSG forever"

/* Window handle function.
 * ARGUMENTS:
 *   - application instance handle:
 *       HINSTANCE hInstance;
 *   - window title:
 *       const CHAR *Title;
 */
tart::win::win( HINSTANCE hInstance, const CHAR* Title )
  : IsInit(), IsActive(), IsFullScreen(), FullScreenSaveRect(), hInstance(hInstance), hWnd(hWnd)
{
  WNDCLASS wc;
  HWND hWnd;

  wc.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS; // Window style: fully redraw if changing any size
  wc.cbClsExtra = 0;                               // Additional byte number for class
  wc.cbWndExtra = sizeof(win*);                    // Additional byte number for window
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;         // Background color
  wc.hCursor = LoadCursor(nullptr, IDC_CROSS);     // Cursor
  wc.hIcon = LoadIcon(nullptr, IDI_ASTERISK);      // Icon
  wc.lpszMenuName = nullptr;                       // Menu name
  wc.hInstance = hInstance;                        // Register class app descriptor
  wc.lpfnWndProc = WinFunc;
  wc.lpszClassName = WND_CLASS_NAME;               // Window class name

  // Register class in system
  if (!RegisterClass(&wc))
  {
    MessageBox(nullptr, (LPCSTR)"Error register window class", (LPCSTR)"ERROR", MB_OK);
    exit(0);
  }

  // Create a window
  hWnd =
    CreateWindow(WND_CLASS_NAME,        // Window class name
      Title,                            // Header
      WS_OVERLAPPEDWINDOW | WS_VISIBLE, // Win style
      CW_USEDEFAULT, CW_USEDEFAULT,     // Win position (x, y)
      CW_USEDEFAULT, CW_USEDEFAULT,     // Win size (w, h)
      nullptr,                          // Parent win descriptor
      nullptr,                          // Menu descriptor
      hInstance,                        // App descriptor
      reinterpret_cast<VOID*>(this));   // Pointer to additional parameters

  // Show and redraw window
  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);
} /* End of 'win::win' function */

/* END OF 'win.cpp' FILE */
