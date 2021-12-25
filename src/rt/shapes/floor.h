/* FILE NAME   : floor.h
 * PROGRAMMER  : TT6
 * LAST UPDATE : 19.12.2021
 * PURPOSE     : Floor data.
 */

#ifndef __floor_h
#define __floor_h

#include "../rt_def.h"

/* Project namespace */
namespace tart
{
  /* Floor store data & check intersection class */
  class floor : public shape
  {
  private:
    vec3 N, P; // (A,B,C)
    FLT D;

  public:
    /* Floor default constructor.
     * ARGUMENTS: None.
     */
    floor( VOID ) : N(0,1,0), P(0), D(0)
    {
    } /* End of 'floor' function */

    /* Floor constructor.
     * ARGUMENTS:
     *   - floor's normal:
     *       vec3 Normal;
     *   - random point on the plane:
     *       vec3 P;
     *   - floor's distance from zero:
     *       FLT d;
     */
    floor( vec3 Normal, vec3 Point, FLT d )
        : N(Normal), P(Point), D(d)
    {
    } /* End of 'floor' function */

    /* Intersect function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &R;
     *   - intr *I;
     * RETURNS:
     *   (BOOL) - TRUE if the ray intersects the object
     *     else FALSE.
     */
    BOOL Intersect( const ray &R, intr *I ) override
    {
      /// I->T = -(N & P + D) / (N & D);
      /// return FALSE;
      /// 
      // First, check if we intersect
      float dDotN = vec3::VecDotVec(R.Dir, N);

      if (dDotN < Treshold)
      {
        // We just assume the ray is not embedded in the plane
        return false;
      }

      // Find point of intersection
      FLT t = vec3::VecSubVec(P, R.Org) & N / dDotN;

      if (t <= Treshold || t >= I->T)
      {
        // Outside relevant range
        return false;
      }

      I->T = t;
      return true;
    } /* End of 'Intersect' function */

    /* Get normal function.
     * ARGUMENT:
     *   - intr *I;
     * RETURNS: None.
     */
    VOID GetNormal( intr* I ) override
    {
    } /* End of 'GetNormal' function */

  }; /* End of 'floor' class */
} /* End of 'tart' namespace */

#endif /* __sphere_h */

/* END OF 'sphere.h' FILE */
