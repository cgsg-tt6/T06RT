/* FILE NAME   : mth_vec3.h
 * PROGRAMMER  : TT6
 * LAST UPDATE : 26.08.2021
 * PURPOSE     : Math 3D vector library.
 * COMMENT     : For ray tracing: operator* and operator *= were added.
 */

#ifndef __mth_vec3_h
#define __mth_vec3_h

#include "mth_def.h"

/* Math library namespace */
namespace mth
{
  /* 3D vector representation type */
  template<typename T>
  class vec3
  {
  private:
    DBL PI = 3.14159265358979323846;

    #define PI 3.14159265358979323846

    /* Degrees to radians conversion */
    #define D2R(A) ((A) * (PI / 180.0))
    #define R2D(A) ((A) * (180.0 / PI))
    #define Degree2Radian(a) D2R(a)

  public:
    T X, Y, Z;

    /* Vec3 default set function.
     * ARGUMENTS: None.
     */
    vec3( VOID ) : X(0), Y(0), Z(0)
    {
    } /* End of 'vec3' function */
    
    /* Vec3 set function.
     * ARGUMENTS:
     *   - coordinate (one parameter for X, Y, Z):
     *       T a;
     */
    vec3( T a ) : X(a), Y(a), Z(a)
    {
    } /* End of 'vec3' function */

    /* Vec3 set function.
     * ARGUMENTS:
     *   - coordinates:
     *       T a, b, c for T X, Y, Z;
     */
    vec3( T a, T b, T c ) : X(a), Y(b), Z(c)
    {
    } /* End of 'vec3' function */

    /* Addition function.
     * ARGUMENTS:
     *   - vector to be added:
     *       const vec3 &V
     * RETURNS:
     *   (vec3) summary vector.
     */
    vec3 operator+( const vec3 &V ) const
    {
      return vec3(X + V.X, Y + V.Y, Z + V.Z);
    } /* End of 'operator+' function */

    /* Addition to this.
     * ARGUMENTS:
     *   - vector to be added:
     *       const vec3 &V;
     * RETURNS:
     *   (vec3 &) self reference.
     */
    vec3 & operator+=( const vec3 &V )
    {
      X += V.X;
      Y += V.Y;
      Z += V.Z;
      return *this;
    } /* End of '& operator+=' function */

    /* Substraction from this.
     * ARGUMENTS:
     *   - vector to be substracted from this:
     *       const vec3 &V;
     * RETURNS:
     *   (vec3 &) self reference.
     */
    vec3 & operator-=( const vec3 &V )
    {
      X -= V.X;
      Y -= V.Y;
      Z -= V.Z;
      return *this;
    } /* End of '& operator-=' function */

    /* Negative vector function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec3) negative vector.
     */
    vec3 operator-( VOID )
    {
      return vec3(-X, -Y, -Z);
    } /* End of 'operator-' function */

    /* Dot multiply two vectors function.
     * ARGUMENTS:
     *   - vector to be product by:
     *       const vec3 &V;
     * RETURNS:
     *   (FLT) result scalar.
     */
    FLT operator&( const vec3 &V ) const
    {
      return X * V.X + Y * V.Y + Z * V.Z;
    } /* End of 'operator&' function */

    /* Count vector length function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (FLT) the length.
     */
    FLT operator!( VOID ) const
    {
      return sqrt(X * X + Y * Y + Z * Z);
    } /* End of 'operator!' function */

    /* Component wise vector multiplication function.
     * ARGUMENTS:
     *   - vector to be product by:
     *       const vec3 &V;
     * RETURNS:
     *   (vec3) vector of component multiplication.
     */
    vec3 operator*( const vec3& V ) const
    {
      vec3 r = vec3(X * V.X, Y * V.Y, Z * V.Z);
      return r;
    } /* End of 'operator*' function */

    /* Component wise vector multiplication function.
     * ARGUMENTS:
     *   - vector to be product by:
     *       const vec3 &V;
     * RETURNS:
     *   (vec3 &) vector of component multiplication.
     */
    vec3 & operator*=( const vec3& V )
    {
      X *= V.X, Y *= V.Y, Z *= V.Z;
      return *this;
    } /* End of 'operator*=' function */

    /* Division on number function.
     * ARGUMENTS:
     *   - number to be divided on:
     *       FLT N;
     * RETURNS:
     *   (vec3) result vector.
     */
    vec3 operator/( FLT N ) const
    {
      return vec3(X / N, Y / N, Z / N);
    } /* End of 'operator/' function */

    /* Normalize vector function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec3) this normalized vector.
     */
    vec3 Normalize( VOID ) const
    {
      return *this / !*this;
    } /* End of 'Normalize' function */

    /* Normalize vector function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec3) this normalized vector.
     */
    vec3 Normalizing( VOID ) const
    {
      vec3 N = *this / !*this;
      return N;
    } /* End of 'Normalizing' function */

    FLT operator[]( INT i ) const
    {
      if (i == 0)
        return X;
      return Y;
    } /* End of 'operator[]' function */

    FLT & operator[]( INT i )
    {
      if (i == 0)
        return X;
      return Y;
    } /* End of '& operator[]' function */

    FLT Distance( const vec3 &V ) const
    {
      return sqrt(X - V.X) + sqrt(Y - V.Y) + sqrt(Z - V.Z);
    } /* End of 'Distance' function */

    /* Substuct two vectors function.
     * ARGUMENTS:
     *   - vectors to be substracted:
     *       vec3 V1, V2;
     * RETURNS:
     *   (vec3) result vector.
     */
    static vec3 VecSubVec( vec3 V1, vec3 V2 )
    {
      return vec3(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
    } /* End of 'VecSubVec' function */

    /* Multiply vector and num function.
     * ARGUMENTS:
     *   - vectors to be multiplied:
     *       vec3 V1;
     *   - num to be multiplied:
     *       FLT N;
     * RETURNS:
     *   (vec3) result vector.
     */
    vec3 VecMulNum( vec3 V1, FLT N )
    {
      return vec3(V1.X * N, V1.Y * N, V1.Z * N);
    } /* End of 'VecMulNum' function */

    vec3 operator*( const FLT N ) const
    {
      vec3 r = vec3(N * X, N * Y, N * Z);
      return r;
    } /* End of 'operator*' function */

    /* NEED THIS FOR MATRVIEW ONLY
     * Normalize vector function.
     * ARGUMENTS:
     *   - vector to be normalized:
     *       VEC V;
     * RETURNS:
     *   (vec3) result vector.
     */
    static vec3 VecNormalize( vec3 V )
    {
      FLT len = V & V;

      if (len == 1 || len == 0)
        return V;
      len = sqrt(len);
      return V / len; // VecDivNum(V, len);
    } /* End of 'VecNormalize' function */

    /* NEED THIS FOR MATRVIEW ONLY
     * Dot multiply two vectors function.
     * ARGUMENTS:
     *   - vectors to be dot multiplied:
     *       vec3 V1, V2;
     * RETURNS:
     *   (FLT) result scalar.
     */
    static FLT VecDotVec( vec3 V1, vec3 V2 )
    {
      return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
    } /* End of 'VecDotVec' function */

    /* Cross multiply two vectors function.
     * ARGUMENTS:
     *   - vectors to be dot multiplied:
     *       vec3 V1, V2;
     * RETURNS:
     *   (vec3) result vector.
     */
    static vec3 VecCrossVec( vec3<T> V1, vec3<T> V2 )
    {
      vec3 v =
      {
        V1.Y * V2.Z - V1.Z * V2.Y,
        -V1.X * V2.Z + V1.Z * V2.X,
        V1.X * V2.Y - V1.Y * V2.X,
      };

      return v;
    } /* End of 'VecCrossVec' function */

    /* Calculate vector lenght function.
     * ARGUMENTS:
     *   - vector:
     *       vec3 V;
     * RETURNS:
     *   (FLT) result lenght.
     */
    static FLT VecLen( vec3 V )
    {
      FLT len = V & V;
 
      if (len == 1 || len == 0)
        return len;
      return sqrt(len);
    } /* End of 'VecLen' function */

    /* Calculate vector squared lenght function.
     * ARGUMENTS:
     *   - vector:
     *       vec3 V;
     * RETURNS:
     *   (FLT) result squared lenght.
     */
    static FLT VecLen2( vec3 V )
    {
      return V & V;
    } /* End of 'VecLen2' function */

    /* Zero vector returning function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec3) null vetor.
     */
    static vec3 Zero(VOID)
    {
      vec3 r;

      r.X = 0;
      r.Y = 0;
      r.Z = 0;
      return r;
    } /* End of 'Zero' function */

  }; /* End of 'vec3' class */
} /* End of 'mth' namespace */

#endif /* __mth_vec3_h */

/* END OF 'mth_vec3.h' FILE */
