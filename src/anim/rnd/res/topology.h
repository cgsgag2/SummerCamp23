/* FILE NAME   : topology.h
 * PROGRAMMER  : AG2
 * LAST UPDATE : 02.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               Topology handle module.
 */

#ifndef __topology_h_
#define __topology_h_

#include "def.h"

#include <vector>

namespace aggl
{
  /* Primitive shape representation type */
  enum struct prim_type
  {
    TRIMESH, /* Triangle mesh */
    POINTS,  /* Points collection */
    STRIP,   /* Strip of triangles */
    LINES    /* Line segments (by 2 points) */
  }; /* End of 'prim_type' enum */
 
  /* Vertex collection namespace */
  namespace vertex
  {
    /* Standard vertex representation type */
    struct std
    {
      vec3 P;  /* Vertex position */
      vec2 T;  /* Vertex texture coordinates */
      vec3 N;  /* Normal at vertex */
      vec4 C;  /* Vertex color */
    }; /* End of 'std' structure */
 
    /* The only point vertex representation type */
    struct point
    {
      vec3 P;  /* Vertex position */
    }; /* End of 'point' structure */
  } /* end of 'vertex' namespace */
 
  /* Topology structures namespase */
  namespace topology
  {
    /* Base topology class */
    template<class vertex_type>
      class base
      {
        friend class prim;
      //protected:
      public:
        prim_type Type = prim_type::TRIMESH;
 
        /* Vertex array */
        std::vector<vertex_type> V;
        /* Index array */
        std::vector<INT> I;
      public:
        /* Class default constructor */
        base( VOID )
        {
        } /* End of 'base' function */
 
        /* Class constructor.
         * ARGUMENTS:
         *   - primitive type:
         *       prim_type NewType;
         *   - vertex array:
         *       const std::vector<vertex_type> &NewV;
         *   - index array:
         *       const std::vector<INT> &NewI;
         */
        base( prim_type NewType,
              const std::vector<vertex_type> &NewV = {},
              const std::vector<INT> &NewI = {} ) :
          Type(NewType), V(NewV), I(NewI)
        {
        } /* End of 'base' function */
      }; /* End of 'base' class */
 
    /* Trimesh topology class */
    template<class vertex_type>
      class trimesh : public base<vertex_type>
      {
      public:
        /* Class constructor.
         * ARGUMENTS:
         *   - vertex array:
         *       const std::vector<vertex> &NewV;
         *   - index array:
         *       const std::vector<INT> &NewI;
         */
        trimesh( const std::vector<vertex_type> &NewV,
                 const std::vector<INT> &NewI = {} ) :
          base<vertex_type>(prim_type::TRIMESH, NewV, NewI)
        {
        } /* End of 'trimesh' function */
 
        // Do later!!!
        // VOID EvalNormals( VOID ) ???
        // VOID EvalTangentSpace( VOID ) ???
      }; /* End of 'trimesh' class */
  } /* end of 'topology' namespace */
} /* end of 'aggl' namespace */

#endif /* __topology_h_ */

/* END OF 'topology.h' FILE */
