/* FILE NAME   : mth_vec4.h
 * PROGRAMMER  : TT6
 * LAST UPDATE : 26.08.2021
 * PURPOSE     : Math 4D vector library.
 */

#ifndef __mth_vec4_h
#define __mth_vec4_h

#include "mth_def.h"

/* Math library namespace */
namespace mth
{
  /* 4D vector representation type */
  template<typename T>
  class vec4
  {
  private:
    // DBL PI = 3.14159265358979323846;

  public:
    T X, Y, Z, W;

    /* Vec4 set function.
     * ARGUMENTS: None.
     */
    vec4( VOID ) : X(0), Y(0), Z(0), W(0)
    {
    } /* End of 'vec4' function */

    /* Vec4 set function.
     * ARGUMENTS:
     *   - coordinate (the same for X, Y, Z, W):
     *       T A;
     */
    vec4( T A ) : X(A), Y(A), Z(A), W(A)
    {
    } /* End of 'vec4' function */

    /* Vec4 set function.
     * ARGUMENTS:
     *   - coordinates:
     *       T A, T B, T C, T D 
     *         for T X, Y, Z, W;
     */
    vec4( T A, T B, T C, T D ) : X(A), Y(B), X(C), W(D)
    {
    } /* End of 'vec4' function */

  }; /* End of 'vec4' class */
} /* End of 'mth' namespace */

#endif /* __mth_vec4_h */

/* END OF 'mth_vec4.h' FILE */
