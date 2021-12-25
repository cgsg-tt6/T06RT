/* FILE NAME   : sphere.h
 * PROGRAMMER  : TT6
 * LAST UPDATE : 18.12.2021
 * PURPOSE     : Sphere data.
 */

#ifndef __sphere_h
#define __sphere_h

#include "../rt_def.h"

/* Project namespace */
namespace tart
{
  /* Sphere store data & check intersection class */
  class sphere : public shape
  {
  private:
    vec3 C;     // coordinates of sphere centre
    FLT R, R2;  // sphere radius + squared

  public:
    /* Sphere make default function.
     * ARGUMENTS: None.
     */
    sphere( VOID )
      : C(vec3(0)), R(1), R2(1)
    {
    } /* End of 'sphere' function */

    /* Sphere make function.
     * ARGUMENTS: 
     *   - sphere centre coordinates:
     *       vec3 C;
     *   - sphere radius:
     *       FLT R;
     */
    sphere( vec3 C, FLT R )
      : C(C), R(R), R2(R * R)
    {
    } /* End of 'sphere' function */

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
      vec3 a = vec3::VecSubVec(C, R.Org);
      DBL oc2 = a & a,
          ok = a & R.Dir,
          ok2 = ok * ok,
          h2 = R2 - (oc2 - ok2);  // double th pif

      // ray starts inside the sphere
      if (oc2 < R2)
      {
        I->T = ok + sqrt(h2);
        return TRUE;
      }
      // ray passes the sphere
      if (ok < 0)
        return FALSE;
      if (h2 < 0)
        return FALSE;
      // else: ray starts outside the sphere
      I->T = ok - sqrt(h2);
      return TRUE;
    } /* End of 'Intersect' function */

    /* Get normal function.
     * ARGUMENT:
     *   - intr *I;
     * RETURNS: None.
     */
    VOID GetNormal( intr *I ) override
    {
      I->N = vec3::VecSubVec(I->P, C).Normalizing();
    } /* End of 'GetNormal' function */
  }; /* End of 'sphere' class */
} /* End of 'tart' namespace */

#endif /* __sphere_h */

/* END OF 'sphere.h' FILE */
