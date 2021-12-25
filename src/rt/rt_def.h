/* FILE NAME   : rt_def.h
 * PROGRAMMER  : TT6
 * LAST UPDATE : 26.08.2021
 * PURPOSE     : Ray tracing main module.
 */

#ifndef __rt_def_h
#define __rt_def_h

#include "../def.h"

/* Project namespace */
namespace tart
{
  const DBL Treshold = 0.000001;

  /* Intersection store class */
  class intr
  {
  public:
    DBL T;  // point of intersection
    vec3 N, // normal
         P; // pos
    // BOOL IsN, IsP; // flag
  }; /* End of 'intr' class */

  /* Geometry shape class */
  class shape
  {
  public:
    /* Intersect function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &R;
     *   - intr *I;
     * RETURNS:
     *   (BOOL) - TRUE if the ray intersects the object
     *              else FALSE.
     */
    virtual BOOL Intersect( const ray &R, intr *I )
    {
      return FALSE;
    } /* End of 'Intersect' function */

    /* Get normal function.
     * ARGUMENT:
     *   - intr *I;
     * RETURNS: None.
     */
    virtual VOID GetNormal( intr *I )
    {
    } /* End of 'GetNormal' function */
  }; /* End of 'shape' class */

  /* Scene handle class */
  class scene
  {
  private:
    stock<shape *> Shapes;
  
  public:
    /* Scene destructor */
    ~scene( VOID )
    {
      for (INT i = 0; i < Shapes.size(); i++)
        delete[] Shapes[i];
    } /* End of 'scene' function */

    /* Add a new shape scenefunction.
     * ARGUMENT:
     *   - new shape:
     *       shape *Shp;
     * RETURNS:
     *   (scene &) self reference.
     */
    scene & operator<<( shape *Shp )
    {
      Shapes << Shp;
      return *this;
    } /* End of 'operator<<' function */
  }; /* End of 'scene' class */
} /* End of 'tart' namespace */

#endif /* __rt_def_h */

/* END OF 'rt_def.h' FILE */
