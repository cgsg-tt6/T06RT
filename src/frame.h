/* FILE NAME   : frame.h
 * PROGRAMMER  : TT6
 * LAST UPDATE : 26.08.2021
 * PURPOSE     : Image frame buffer.
 */

#ifndef __frame_h_
#define __frame_h_

#include "def.h"

/* Project namespace */
namespace tart
{
  /* Frame buffer handle class */
  class frame
  {
  private:
    DWORD *Pixels = nullptr; // Frame buffer pixels

  public:
    // Frame size
    INT W = 0, H = 0;

    /* Resize frame buffer function.
     * ARGUMENTS:
     *   - new frame size:
     *       INT NewW, NewH;
     * RETURNS: None.
     */
    VOID Resize( INT NewW, INT NewH )
    {
      if (Pixels != nullptr)
        delete[] Pixels;
      W = H = 0;
      if (NewW != 0 && NewH != 0)
      {
        Pixels = new DWORD[NewW * NewH];
        ZeroMemory(Pixels, NewW * NewH * 4);
        W = NewW;
        H = NewH;
      }
    } /* End of Resize' function */

    /* Put pixel with specified color function.
     * ARGUMENTS:
     *   - pixel coordinates:
     *       INT X, Y;
     *   - pixel color:
     *       DWORD Color;
     * RETURNS: None.
     */
    VOID PutPixel( INT X, INT Y, DWORD Color )
    {
      // Clipping
      if (X < 0 || Y < 0 || X >= W || Y >= H)
        return;
 
      // Set pixel color
      Pixels[Y * W + X] = Color;
    } /* End of 'PutPixel' function */

    /* Blit frame to device context function.
     * ARGUMENTS:
     *   - device context:
     *       HDC hDC;
     *   - window coordinates:
     *       INT X, Y;
     * RETURNS: None.
     */
    VOID Draw( HDC hDC, INT X, INT Y )
    {
      BITMAPINFOHEADER bih;

      bih.biSize = sizeof(BITMAPINFOHEADER);
      bih.biBitCount = 32;
      bih.biPlanes = 1;
      bih.biWidth = W;
      bih.biHeight = -H;
      bih.biSizeImage = W * H * 4;
      bih.biCompression = BI_RGB;
      bih.biClrUsed = 0;
      bih.biClrImportant = 0;
      bih.biXPelsPerMeter = 30;
      bih.biYPelsPerMeter = 30;

      SetStretchBltMode(hDC, COLORONCOLOR);
      StretchDIBits(hDC, X, Y, W, H, 0, 0, W, H, Pixels,
        (BITMAPINFO *)&bih, DIB_RGB_COLORS, SRCCOPY);
    } /* End of 'Draw' function */

    /* Convert float point 0..1 range color to DWORD function.
     * ARGUMENTS:
     *   - color RGB values:
     *       FLT R, G, B;
     * RETURNS:
     *   (DWORD) result packed color.
     */
    static DWORD ToRGB( FLT R, FLT G, FLT B )
    {
      auto clamp =
        []( FLT Value ) -> BYTE
        {
          if (Value < 0)
            return 0;
          if (Value > 1)
            return 255;
          return Value * 255;
        };
      return (clamp(R) << 16) | (clamp(G) << 8) | clamp(B);
    } /* End of 'ToRGB' function */

    /* Class destructor */
    ~frame( VOID )
    {
      Resize(0, 0);
    } /* End of '~frame' function */
  }; /* End of 'frame' class */
} /* End of 'tart' namespace */

#endif /* __frame_h_ */

/* END OF 'frame.h' FILE */
