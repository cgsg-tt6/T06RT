/* FILE NAME   : mth_camera.h
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               Vitaly A. Galinsky. (+TT6)
 * LAST UPDATE : 26.08.2021.
 * PURPOSE     : Animation project.
 *               Mathematics library.
 *               Space camera handle module.
 * NOTE        : Module namespace 'mth'.
 * COMMENT     : For ray tracing: FrameToRay function added.
 */

#ifndef __mth_camera_h_
#define __mth_camera_h_

#include "mth_vec3.h"
#include "mth_matr.h"
#include "mth_ray.h"

/* Math library namespace */
namespace mth
{
  /* Space camera handle class */
  template<class type = FLT>
    class camera
    {
    private:
      /* Update camera project parameters function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID UpdateProj( VOID )
      {
        type ratio_x = Size / 2, ratio_y = Size / 2;

        if (FrameW >= FrameH)
          ratio_x *= (type)FrameW / FrameH;
        else
          ratio_y *= (type)FrameH / FrameW;
        Wp = ratio_x * 2;
        Hp = ratio_y * 2;
        Proj = matr<type>::MatrFrustum(-ratio_x, ratio_x, -ratio_y, ratio_y, ProjDist, FarClip);
      } /* End of 'UpdateProj' function */

      /* Update camera view parameters function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID UpdateView( VOID )
      {
        View = matr<type>::MatrView(Loc, At, Up);
      } /* End of 'UpdateView' function */

    public:
      // For render
      vec3<type>
        Loc,            // camera location
        Dir, Up, Right, // basis camera directions
        At;             // camera pilot point
      type
        ProjDist,       // near  project plane distance
        FarClip,        // far   project plane distance
        Size,           // inner project plane rectangle size
        Wp, Hp;
      INT
        FrameW, FrameH; // Camera frame size
      matr<type>
        View,           // view matrix
        Proj,           // projection matrix
        VP;             // View and Proj madtriX production

      /* Default constructor = CamSet.
       * ARGUMENTS: None.
       */
      camera( VOID ) :
        Loc(0, 0, 5), Dir(0, 0, -1), Up(0, 1, 0), Right(1, 0, 0), At(0, 0, 0),
        ProjDist(0.1), FarClip(500), Size(0.1),
        FrameW(30), FrameH(30)
      {
        UpdateProj();
        UpdateView();
        VP = View * Proj;
      } /* End of 'matr' function */

      /* Set project camera parameters function.
       * ARGUMENTS:
       *   - new near project plane size:
       *       type NewSize;
       *   - new project distance:
       *       type NewProjDist;
       *   - new far clip plane distance:
       *       type FarC;
       * RETURNS:
       *   (camera &) self reference.
       */
      camera & SetProj( type NewSize, type NewProjDist, type NewFarClip )
      {
        // Store new projection parameters
        ProjDist = NewProjDist;
        FarClip = NewFarClip;
        Size = NewSize;

        UpdateProj();
        VP = View * Proj;
        return *this;
      } /* End of 'SetProj' function */

      /* Set camera project piXel size function.
       * ARGUMENTS:
       *   - new frame size in piXels:
       *       type NewFrameW, NewFrameH;
       * RETURNS:
       *   (camera &) self reference.
       */
      camera & Resize( type NewFrameW, type NewFrameH )
      {
        FrameW = NewFrameW;
        FrameH = NewFrameH;

        UpdateProj();
        VP = View * Proj;
        return *this;
      } /* End of 'Resize' function */

      /* Set camera location and orientation function.
       * ARGUMENTS:
       *   - new camera location:
       *       const vec3<type> &L;
       *   - new camera pivot point:
       *       const vec3<type> &A;
       *   - new camera approX up direction:
       *       const vec3<type> &U;
       * RETURNS:
       *   (camera &) self reference.
       */
      camera & SetLocAtUp( const vec3<type> &L, const vec3<type> &A, const vec3<type> &U = vec3<type>(0, 1, 0) )
      {
        Loc = L;
        At = A;
        Up = U;

        UpdateView();
        VP = View * Proj;
        return *this;
      } /* End of 'SetLocAtUp' function */

      /* Camera rotate function.
       * ARGUMENTS:
       *   - rotate axis:
       *       const vec3<type> &Axis;
       *   - rotation angle (in degree):
       *       type AngleInDegree;
       * RETURNS:
       *   (camera &) self reference.
       */
      camera & Rotate( const vec3<type> &Axis, type AngleInDegree )
      {
        matr<type> m = matr<type>::MatrTranslate(-At) * matr<type>::MatrRotate(Axis, AngleInDegree) * matr<type>::MatrTranslate(At);
        Loc = m.PointTransform(Loc, m);
        Up = m.VectorTransform(Up, m);
        SetLocAtUp(Loc, At, Up);
        return *this;
      } /* End of 'Rotate' function */

      /* Camera movement function.
       * ARGUMENTS:
       *   - movement directions:
       *       const vec3<type> &Direction;
       * RETURNS:
       *   (camera &) self reference.
       */
      camera & Move( const vec3<type> &Direction )
      {
        Loc += Direction;
        At += Direction;
        SetLocAtUp(Loc, At, Up);
        return *this;
      } /* End of 'Move' function */

      /* Ray to frame function.
       * ARGUMENTS:
       *   - coordinates:
       *       type Xs, Ys;
       * RETURNS:
       *   (ray) ray.
       */
      ray<type> FrameToRay( type j, type i )
      {
        ray<type> Ray;
        vec3<type> A = Dir * ProjDist,
                   B = Right * (j - FrameW / 2) * Wp / FrameW,
                   C = Up * (FrameH / 2 - i) * Hp / FrameH;
        vec3<type> Q = A + B + C;

        Ray.Org = Loc + Q;
        Ray.Dir = Q.Normalize();

        return Ray;
      } /* End of 'FrameToRay' function */
    }; /* End of 'camera' class */
} /* End of 'mth' namespace */

#endif /* __mth_camera_h_ */

/* END OF 'mth_camera.h' FILE */
