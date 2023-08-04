/* FILE NAME   : mth_ray.h
 * PROGRAMMER  : AG2
 * LAST UPDATE : 30.07.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Math module.
 *               3D math ray module.
 */

#ifndef __mth_ray_h_
#define __mth_ray_h_

#include "mth_def.h"

/* Space math namespace */
namespace mth
{ 
  /* Ray representation type */
  template<typename Type>
    class ray
    {
    public:
      vec3<Type> Org, Dir;  // Ray direction and origin
      /* Ray default constructor */
      ray( VOID )
      {
      }
      /* Ray constructor by vector */
      ray( const vec3<Type> &O, const vec3<Type> &D ) : 
        Org(O), Dir(D.Normalizing())
      {
      }
      
      /*** Overload operations ***/
      
      /* Get position of point at ray function.
       * ARGUMENTS:
       *   - Intersection ray distance:
       *       Type T;
       * RETURNS: 
       *   (vec3) result new vector - position for ray.
       */
      vec3<Type> operator()( Type T ) const
      {
        return Org + Dir * T;
      } /* End of 'operator()' function */
      
    }; /* End of 'ray' class */
} /* end of 'mth' namespace */

#endif /* __mth_ray_h_ */

/* END OF 'mth_ray.h' FILE */
