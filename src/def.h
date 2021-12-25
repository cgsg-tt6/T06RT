/* FILE NAME   : def.h
 * PROGRAMMER  : TT6
 * LAST UPDATE : 26.08.2021
 * PURPOSE     : WinAPI animation project.
 *               Common declaration module.
 */

#ifndef __def_h_
#define __def_h_

#include <cassert>
#include <vector>
#include <commondf.h>

#ifdef _DEBUG
#  define _CRTDBG_MAP_ALLOC
#  include <crtdbg.h>
#  define SetDbgMemHooks() \
     _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
       _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#else /* _DEBUG */
#  define SetDbgMemHooks() ((VOID)0)
#endif /* _DEBUG */
#include <stdlib.h>

#include "mth/mth.h"

/* Large integer types */
typedef long long INT64;
typedef unsigned long long UINT64;

// Define common usage math types
/* Project namespace */
namespace tart
{
  typedef mth::vec2<FLT> vec2;
  typedef mth::vec3<FLT> vec3;
  typedef mth::vec4<FLT> vec4;
  typedef mth::matr<FLT> matr;
  typedef mth::ray<FLT>  ray;
  typedef mth::camera<FLT> camera;

  /* Stock class */
  template<typename type>
    class stock : public std::vector<type>
    {
    public:
      /* Add a new element to stock function.
       * ARGUMENT:
       *   - new element:
       *       const type &NewElement;
       * RETURNS:
       *   (stock &) self reference.
       */
      stock & operator<<( const type &NewElement )
      {
        push_back(NewElement);
        return *this;
      } /* End of 'operator<<' function */
    }; /* End of 'stock' class */
} /* End of 'tart' namespace */

#endif /* __def_h_ */

/* END OF 'def.h' FILE */
