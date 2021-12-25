/* FILE NAME   : win.h
 * PROGRAMMER  : TT6
 * LAST UPDATE : 19.12.2021
 * PURPOSE     : Namespace tart, class win.
 */

#ifndef __win_h
#define __win_h

#include "../def.h"

/* Project namespace */
namespace tart
{
  class win
  {
  protected:
    HWND hWnd;           // window handle
    INT W, H;            // window size
    HINSTANCE hInstance; // application handle

  private:
    BOOL IsInit,
         IsFullScreen;
    RECT FullScreenSaveRect;

    static LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg,
                                     WPARAM wParam, LPARAM lParam );

  public:
    INT MouseWheel;
    BOOL IsActive;

    win( HINSTANCE hInst = GetModuleHandle(NULL), const CHAR* Title = "CGSG forever!!! Ray Tracing Project, Summer Camp 2021" );

    /* Class destructor */
    virtual ~win( VOID )
    {
    } /* End of '~win' function */

    WPARAM Run( VOID );
    static VOID FlipFullScreen( HWND hWnd );

    virtual VOID Render( VOID )
    {
    } /* End of 'Render' function *

    /* Initialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Init( VOID )
    {
    } /* End of 'Init' function */

    /* Close function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Close( VOID )
    {
    } /* End of 'Close' function */

    /* Resize function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Resize( VOID )
    {
    } /* End of 'Resize' function */

    /* Timerfunction.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Timer( VOID )
    {
    } /* End of 'Timer' function */

    /* Activate function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Activate( VOID )
    {
    } /* End of 'Activate' function */

    /* Idle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Idle( VOID )
    {
    } /* End of 'Idle' function */

    /* Erase function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Erase( HDC hDC )
    {
    } /* End of 'Erase' function */

    /* Paint function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Paint( HDC hDC )
    {
    } /* End of 'Paint' function */

  private:
    // Message cracks
    BOOL OnCreate( CREATESTRUCT *CS );
    VOID OnSize( UINT State, INT W, INT H );
    VOID OnTimer( INT Id );
    VOID OnMouseWheel( INT X, INT Y, INT Z, UINT Keys );
    BOOL OnEraseBackground( HDC hDC );
    VOID OnPaint( HDC hDC, PAINTSTRUCT *PS );
    VOID OnClose( VOID );
    VOID OnDestroy( VOID );
    VOID OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized );
  }; /* End of 'win' class */
} /* End of 'tart' namespace */

#endif /* __win_h */

/* END OF 'win.h' FILE */
