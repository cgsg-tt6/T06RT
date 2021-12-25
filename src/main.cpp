/* FILE NAME   : main.cpp
 * PROGRAMMER  : TT6
 * LAST UPDATE : 19.12.2021
 * PURPOSE     : Main project file.
 */

#include <time.h>
#include "timer.h"

#include "win/win.h"
#include "mth/mth.h"
#include "frame.h"
#include "rt/rt_def.h"
#include "rt/rt.h"

#define Le 500

/* Project namespace */
namespace tart
{
  /* Ray to window class */
  class rt_win : public win
  {
  public:
    camera Cam;
    frame Frm;
    scene Scene;

    /* ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Render( VOID )
    {
      LONG t = clock();
      auto ToDW =
        []( const vec3 &V )
        {
          BYTE
            R = V.X < 0 ? 0 : V.X > 1 ? 255 : V.X * 255,
            G = V.Y < 0 ? 0 : V.Y > 1 ? 255 : V.Y * 255,
            B = V.Z < 0 ? 0 : V.Z > 1 ? 255 : V.Z * 255;
          return (R << 16) | (G << 8) | B;
        };

      for (INT y = 0; y < Frm.H; y++)
        for (INT x = 0; x < Frm.W; x++)
        {
          INT z = 0;
          intr Intr;
          sphere Sphere = sphere((0, 1, 0), 10);
          // floor Floor = floor((0,1,0), (x,y,0), 1);

          ray R = Cam.FrameToRay(x + 0.5, y + 0.5);
          vec3 color = R.Dir * 2 + vec3(0.4);
          if (Sphere.Intersect(R, &Intr) /*|| /*Floor.Intersect(R, &Intr)*/)
            Frm.PutPixel(x, y, frame::ToRGB(color.X, color.Y, color.Z)); ///frame::ToRGB(N.X * 1000, N.Y, N.Z));
          else
            Frm.PutPixel(x, y, frame::ToRGB(0.33, 0.53, 0.73));
          z++;
        }
    } /* End of 'Render' function */
    
    /* Initialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Init( VOID ) override
    {
      Cam.
        SetLocAtUp(vec3(0, 0, 10), vec3(0, 0, 0), vec3(0, 1, 0)).
        SetProj(0.1, 0.1, 1000).
        Resize(Le, Le);
      Render();
    } /* End of 'Init' function */

    /* Paint function.
     * ARGUMENT:
     *   - device context:
     *       HDC hDC;
     * RETURNS: None.
     */
    VOID Paint( HDC hDC ) override
    {
      Frm.Draw(hDC, W/2 - Le/2, H/2 - Le/2);
    } /* End of 'Paint' function */

    /* Idle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Idle( VOID ) override
    {
      //error/Cam.Rotate(vec3(1, 0, 0), 30 * clock());
    } /* End of 'Idle' function */

    /* Erase background function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Erase( HDC hDC ) override
    {
      SelectObject(hDC, GetStockObject(WHITE_BRUSH));
      SelectObject(hDC, GetStockObject(NULL_PEN));
      Rectangle(hDC, 0, 0, W + 1, H + 1);
    } /* End of 'Erase' function */

    /* Close function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Close( VOID ) override
    {
    } /* End of 'Close' function */
  }; /* End of 'rt_win' class */
} /* End of 'tart' namespace */

/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    CHAR *CmdLine, INT CmdShow )
{
  tart::rt_win mw;

  mw.Frm.Resize(Le, Le);

  mw.Scene <<
    new tart::sphere(tart::vec3(0), 1) <<
    new tart::sphere(tart::vec3(1,0,0), 100);
  //mw.Frm.Resize(Le, Le);
  return mw.Run();
} /* End of 'WinMain' function */

/* END OF 'main.cpp' FILE */
