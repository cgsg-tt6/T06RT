/* FILE NAME   : mth_vec2.h
 * PROGRAMMER  : TT6
 * LAST UPDATE : 26.08.2021
 * PURPOSE     : Math 2D vector library.
 */

#ifndef __mth_vec2_h
#define __mth_vec2_h

#include "mth_def.h"

/* Math library namespace */
namespace mth
{
  /* 2D vector representation type */
  template<class T>
  class vec2
  {
  private:
    // DBL PI = 3.14159265358979323846;

  public:
    T X, Y;

    /* Vec2 set function.
     * ARGUMENTS: None.
     */
    vec2( VOID ) : X(0), Y(0)
    {
    } /* End of 'vec2' function */

    /* Vec2 set function.
     * ARGUMENTS:
     *   - coordinate (the same both for X and Y):
     *       T a;
     */
    vec2( T a ) : X(a), Y(a)
    {
    } /* End of 'vec2' function */

    /* Vec2 set function.
     * ARGUMENTS:
     *   - coordinates:
     *       T a, b for T X, Y;
     */
    vec2( T a, T b ) : X(a), Y(b)
    {
    } /* End of 'vec2' function */

  }; /* End of 'vec2' class */
} /* End of 'mth' namespace */

#endif /* __mth_vec2_h */

/* END OF 'mth_vec2.h' FILE */
