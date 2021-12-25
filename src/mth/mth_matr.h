/* FILE NAME   : mth_matr.h
 * PROGRAMMER  : TT6
 * LAST UPDATE : 26.08.2021
 * PURPOSE     : Math matrix library.
 */

// NORMAL TRANSFORM (netu)

#ifndef __mth_matr_h
#define __mth_matr_h

#include "mth_def.h"
#include "mth_vec3.h"

/* Math library namespace */
namespace mth
{
  /* 4x4 matrixes representation type */
  template <typename T = FLT>
  class matr
  {
  public:
    T A[4][4];

    /* matrix default constructor.
     * ARGUMENTS: None.
     */
    matr( VOID )
    {
      for (INT i = 0; i < 4; i++)
        for (INT j = 0; j < 4; j++)
          A[i][j] = 0;
    } /* End of 'matr' function */

    /* matrix 4x4 set function.
     * ARGUMENTS:
     *   - Elements to put in matrix:
     *       FLT A11, A21, A31, A41,
     *           A12, A22, A32, A42,
     *           A13, A23, A33, A43,
     *           A14, A24, A34, A44;
     */
    matr( T A11, T A21, T A31, T A41,
          T A12, T A22, T A32, T A42,
          T A13, T A23, T A33, T A43,
          T A14, T A24, T A34, T A44 )
    {
      A[0][0]=A11, A[1][0]=A21, A[2][0]=A31, A[3][0]=A41,
      A[0][1]=A12, A[1][1]=A22, A[2][1]=A32, A[3][1]=A42,
      A[0][2]=A13, A[1][2]=A23, A[2][2]=A33, A[3][2]=A43,
      A[0][3]=A14, A[1][3]=A24, A[2][3]=A34, A[3][3]=A44;
    } /* End of 'matr' function */

    /* Get identity matrix function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (matr) identity matrix.
     */
    static matr MatrIdentity( VOID )
    {
      /* Unit matrix */
      return matr(1, 0, 0, 0,
                  0, 1, 0, 0,
                  0, 0, 1, 0,
                  0, 0, 0, 1);
    } /* End of 'MatrIdentity' function */

    /* Translate matrix function.
     * ARGUMENTS:
     *   - vector to matrix:
     *       vec3 T;
     * RETURNS:
     *   (matr) result matrix.
     */
    matr MatrTranslate( const vec3<T> V )
    {
      matr m = MatrIdentity();

      m.A[3][0] = V.X;
      m.A[3][1] = V.Y;
      m.A[3][2] = V.Z;
      return m;
    } /* End of 'MatrTranslate' function */

    /* SCALE AND ROTATE */

    /* Matrix scaling function.
     * ARGUMENTS:
     *   - vector to matrix:
     *       vec3 S;
     * RETURNS:
     *   (matr) result matrix.
     */
    matr MatrScale( vec3<T> S )
    {
      return matr(S.X, 0, 0, 0,
                  0, S.Y, 0, 0,
                  0, 0, S.Z, 0,
                  0, 0, 0, 1);
    } /* End of 'MatrTranslate' function */

    /* Rotate matrix function.
     * ARGUMENTS:
     *   - angle in degrees:
     *       FLT AngleInDegree;
     *   - vector to matrix:
     *       vec3 T;
     * RETURNS:
     *   (matr) result matrix.
     */
    matr MatrRotate( FLT AngleInDegree, vec3<T> V )
    {
      FLT a = D2R(AngleInDegree), c = cos(a), s = sin(a);
      vec3 A = vec3::VecNormalize(V);

      return matr(c + A.X * A.X * (1 - c), A.X * A.Y * (1 - c) + A.Z * s, A.X * A.Z * (1 - c) - A.Y * s, 0,
                  A.Y * A.X * (1 - c) - A.Z * s, c + A.Y * A.Y * (1 - c), A.Y * A.Z * (1 - c) + A.X * s, 0,
                  A.Z * A.X * (1 - c) + A.Y * s, A.Z * A.Y * (1 - c) - A.X * s, c + A.Z * A.Z * (1 - c), 0,
                  0, 0, 0, 1);
    } /* End of 'MatrRotate' function */

    /* Rotate matrix by X axis function.
     * ARGUMENTS:
     *   - angle in degrees:
     *       FLT AngleInDegree;
     * RETURNS:
     *   (matr) result matrix.
     */
    matr MatrRotateX( FLT AngleInDegree )
    {
      FLT a = D2R(AngleInDegree), c = cos(a), s = sin(a);

      return matr(1, 0, 0, 0,
                  0, c, s, 0,
                  0, -s, c, 0,
                  0, 0, 0, 1);
    } /* End of 'MatrRotateX' function */

    /* Rotate matrix by Y axis function.
     * ARGUMENTS:
     *   - angle in degrees:
     *       FLT AngleInDegree;
     * RETURNS:
     *   (matr) result matrix.
     */
    matr MatrRotateY( FLT AngleInDegree )
    {
      FLT a = D2R(AngleInDegree), c = cos(a), s = sin(a);

      return matr(c, 0, -s, 0,
                  0, 1, 0, 0,
                  s, 0, c, 0,
                  0, 0, 0, 1);
    } /* End of 'MatrRotateY' function */

    /* Rotate matrix by Z axis function.
     * ARGUMENTS:
     *   - angle in degrees:
     *       FLT AngleInDegree;
     * RETURNS:
     *   (matr) result matrix.
     */
    matr MatrRotateZ( FLT AngleInDegree )
    {
      FLT a = D2R(AngleInDegree), c = cos(a), s = sin(a);

      return matr(c, s, 0, 0,
                  -s, c, 0, 0,
                  0, 0, 1, 0,
                  0, 0, 0, 1);
    } /* End of 'MatrRotateZ' function */

    /* Multiply matrix function.
     * ARGUMENTS:
     *   - matrix:
     *       matr M1;
     * RETURNS:
     *   (matr) result matrix.
     */
    matr MatrMulMatr( matr M1 ) const
    {
      matr r;
      INT i, j, k;

      for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
          for (r.A[i][j] = 0, k = 0; k < 4; k++)
            r.A[i][j] += A[i][k] * M1.A[k][j];
      return r;
    } /* End of 'MatrMulMatr' function */
    
    /* Multiply matrix function.
     * ARGUMENTS:
     *   - matrix to be multiplied:
     *       matr m2;
     * RETURNS:
     *   (matr) result matrix.
     */
    matr operator*( matr m2 )
    {
      matr r;
      INT i, j, k;

      for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
          for (r.A[i][j] = 0, k = 0; k < 4; k++)
            r.A[i][j] += A[i][k] * m2.A[k][j];
      return r;
    } /* End of 'operator*' function */

    /* Matrix 3x3 determinant obtain function.
     * ARGUMENTS:
     *   - matrix elements:
     *       A11, A12, A13,
     *       A21, A22, A23,
     *       A31, A32, A33;
     * RETURNS:
     *   (FLT) determinant.
     */
    static FLT MatrDeterm3x3( FLT A11, FLT A12, FLT A13,
                              FLT A21, FLT A22, FLT A23,
                              FLT A31, FLT A32, FLT A33 )
    {
      return A11 * A22 * A33 - A11 * A23 * A32 - A12 * A21 * A33 + 
             A12 * A23 * A31 + A13 * A21 * A32 - A13 * A22 * A31;
    } /* End of 'MatrDeterm3x3' function */

    /* Calculate matrix determinant function.
     * ARGUMENTS:
     *   - matrix:
     *      matr M;
     * RETURNS:
     *   (FLT) determinant.
     */ 
    FLT MatrDeterm( matr M )
    {
      return
        M.A[0][0] * MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                                  M.A[2][1], M.A[2][2], M.A[2][3],
                                  M.A[3][1], M.A[3][2], M.A[3][3]) +
        -M.A[0][1] * MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                                   M.A[2][0], M.A[2][2], M.A[2][3],
                                   M.A[3][0], M.A[3][2], M.A[3][3]) +
        M.A[0][2] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
                                  M.A[2][0], M.A[2][1], M.A[2][3],
                                  M.A[3][0], M.A[3][1], M.A[3][3]) +
        -M.A[0][3] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                                   M.A[2][0], M.A[2][1], M.A[2][2],
                                   M.A[3][0], M.A[3][1], M.A[3][2]);
    } /* End of 'MatrDeterm' function */

    /* This might be incorrect function.
     * ARGUMENTS:
     *   - matrix:
     *       matr M;
     * RETURNS:
     *   (matr) matrix.
     */
    matr MatrInverse( matr M )
    {
      matr r;
      FLT det = MatrDeterm(M);
      INT s, i, j, P[][3] = {{1, 2, 3}, {0, 2, 3}, {0, 1, 3}, {0, 1, 2}};
 
      for (s = 1, i = 0; i < 4; i++)
        for (j = 0; j < 4; j++, s = -s)
          r.A[j][i] =
            s * MatrDeterm3x3(M.A[P[i][0]][P[j][0]], M.A[P[i][0]][P[j][1]], M.A[P[i][0]][P[j][2]],
                              M.A[P[i][1]][P[j][0]], M.A[P[i][1]][P[j][1]], M.A[P[i][1]][P[j][2]],
                              M.A[P[i][2]][P[j][0]], M.A[P[i][2]][P[j][1]], M.A[P[i][2]][P[j][2]]) / det;
      return r;
    } /* End of 'MatrInverse' function */

    /* Vector and matrix multiplication
     * ARGUMENTS:
     *   - vector to be multiplied:
     *       const vec3 V;
     *   - matrix:
     *       matr M;
     * RETURNS:
     *   (vec3) result vector.
     */
    vec3<T> VecMulMatr( const vec3<T> &V, matr M )
    {
      vec3 v;
      FLT w;
    
      w   =  V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3] + M.A[3][3];
      v.X = (V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0]) / w;
      v.Y = (V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1]) / w;
      v.Z = (V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]) / w;
    
      return v;
    } /* End of 'VecMultMatr' function */

    /* Transform point position.
     * ARGUMENTS:
     *   - radius-vector (point coordinates) to be transformed:
     *       const vec3 V;
     *   - matrix:
     *       matr M;
     * RETURNS:
     *   (vec3) result vector.
     */
    vec3<T> PointTransform( const vec3<T> &V, matr M )
    {
      vec3<T> r;

      r.X = V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0];
      r.Y = V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1];
      r.Z = V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2];

      return r;
    } /* End of 'PointTransform' function */

    /* Transform vector position.
     * ARGUMENTS:
     *   - vector to be transformed:
     *       const vec3 V;
     *   - matrix:
     *       matr M;
     * RETURNS:
     *   (vec3) result vector.
     */
    vec3<T> VectorTransform( const vec3<T> &V, matr M )
    {
      return VecMulMatr(V, M);
    } /* End of 'VectorTransform' function */

    // NormalTransform

    /* Normalized device coordinates function.
     * ARGUMENTS:
     *   - Screen factors:
     *      Left and Right:
     *        FLT L, R;
     *      Bottom and Top:
     *        FLT B, T;
     *      Near and Far:
     *        FLT N, F;
     * RETURNS:
     *   (matr) result matrix.
     */
    static matr MatrFrustum( FLT L, FLT R, FLT B, FLT T, FLT N, FLT F )
    {
      return matr(2 * N / (R - L), 0, 0, 0,
                  0, 2 * N / (T - B), 0, 0,
                  (R + L) / (R - L), (T + B) / (T - B), -(F + N) / (F - N), -1,
                  0, 0, -2 * N * F / (F - N), 0);
    } /* End of 'MatrFrustum' function */

    /* View projection matrix set function.
     * ARGUMENTS:
     *   - position vectors:
     *       vec3<T> Loc, At, Up1;
     * RETURNS:
     *   (matr) matrix.
     */
    static matr MatrView( vec3<T> Loc, vec3<T> At, vec3<T> Up1 )
    {
      vec3<T>
        Dir = vec3<T>::VecNormalize(vec3<T>::VecSubVec(At, Loc)),
        Right = vec3<T>::VecNormalize(vec3<T>::VecCrossVec(Dir, Up1)),
        Up = vec3<T>::VecNormalize(vec3<T>::VecCrossVec(Right, Dir));
      return matr(Right.X, Up.X, -Dir.X, 0,
                  Right.Y, Up.Y, -Dir.Y, 0,
                  Right.Z, Up.Z, -Dir.Z, 0,
                  0.0 - vec3<T>::VecDotVec(Loc, Right),
                  0.0 - vec3<T>::VecDotVec(Loc, Up), vec3<T>::VecDotVec(Loc, Dir), 1);
    } /* End of 'MatrView' function */

    /* Ortho projection matrix function.
     * ARGUMENTS:
     *   - Screen factors:
     *      Left and Right:
     *        FLT L, R;
     *      Bottom and Top:
     *        FLT B, T;
     *      Near and Far:
     *        FLT N, F;
     * RETURNS:
     *   (matr) viewer matrix.
     */
    matr MatrOrtho( FLT L, FLT R, FLT B, FLT T, FLT N, FLT F )
    {
      return matr(2 / (R - L),              0,                        0,                 0,
                  0,                        2 / (T - B),              0,                 0,
                  0,                        0,                       -2 / (F - N),       0,
                 -(R + L) / (R - L),       -(T + B) / (T - B),       -(N + F) / (F - N), 1);
    } /* End of 'MatrOrtho' function */

  }; /* End of 'matr' class */
} /* End of 'mth' namespace */

#endif /* __mth_matr_h */

/* END OF 'mth_matr.h' FILE */
