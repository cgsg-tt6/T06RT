/* FILE NAME   : mth_ray.h
 * PROGRAMMER  : TT6
 * LAST UPDATE : 26.08.2021
 * PURPOSE     : Ray support.
 */

#ifndef __mth_ray_h
#define __mth_ray_h

#include "mth_def.h"

/* Math library namespace */
namespace mth
{
  // Ray vector representation type
  template<typename T>
  class ray
  {
  public:
    vec3<T> Org, // position: Loc, Up, Right
            Dir; // direction
    
    /* Ray default constructor.
     * ARGUMENTS: None.
     */
    ray( VOID )
    {
    } /* End of 'ray' function */

    /* Ray constructor.
     * ARGUMENTS: 
     *   - origin:
     *       const vec3<T> &O;
     *   - direction:
     *       const vec3<T> &D;
     */
    ray( const vec3<T> &O, const vec3<T>& D ) : Org(O), Dir(D)
    {
      Dir.Normalize();
    } /* End of 'ray' function */

    /* Obtain ray point function.
     * ARGUMENTS:
     *   - ray parameter:
     *       T RayT;
     * RETURNS:
     *   (vec3<T>) result ray point.
     */
    vec3<T> operator()( T RayT )
    {
      return Org + Dir * RayT;
    } /* End of 'operator()' function */
  }; /* End of 'ray' class */
} /* End of 'mth' namespace */

#endif /* __mth_ray_h */

/* END OF 'mth_ray.h' FILE */
