/* FILE NAME   : primitives.h
 * PROGRAMMER  : AG2
 * LAST UPDATE : 02.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               Primitives and primitives' manager handle module.
 */

#ifndef __primitives_h_
#define __primitives_h_

#include "def.h"

#include "material.h"
#include "topology.h"

#include <iostream>

/* Project namespace */
namespace aggl
{
  /* Primitives representation type */
  class prim
  {
    friend class render;
    
  private:
    prim_type Type {};  // Primitive type
    UINT VA;            // Primitive vertex array
    UINT VBuf;          // Vertex buffer
    UINT IBuf;          // Index buffer
    INT NumOfElements;  // Number of elements for OpenGL
    matr Transform {};  // Primitive transformation matrix
  public:
    material *Mtl {};   // Pointer to material
    vec3
      Min {0},          // Minimal primitive position
      Max {0};          // Maximal primitive position

    /* Primitives default constructor */
    prim( VOID )
    {
    } /* End of 'prim' function */

    /* Primitive creation function.
     * ARGUMENTS:
     *   - topology base reference:
     *       const topology::base &T;
     *   - pointer to material for primitive:
     *       material *Mat;
     * RETURNS:
     *   (prim &) self reference.
     */
    template<class vertex>
      prim & Create( material *Mat, const topology::base<vertex> &T )
      {
        if (!T.V.empty())
        {
          glGenBuffers(1, &VBuf);
          glGenVertexArrays(1, &VA);
          /* Vertex data */
          glBindVertexArray(VA);
          /* Active buffer */
          glBindBuffer(GL_ARRAY_BUFFER, VBuf);
          /* Merge data */
          glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * T.V.size(), T.V.data(), GL_STATIC_DRAW);
          
          glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(vertex),
                                (VOID *)0); /* position */
          glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(vertex),
                                (VOID *)sizeof(vec3)); /* texture coordinates */
          glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(vertex),
                                (VOID *)(sizeof(vec3) + sizeof(vec2))); /* normal */
          glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(vertex),
                                (VOID *)(sizeof(vec3) * 2 + sizeof(vec2))); /* color */
           
          /* Include the necessary attributes (layout) */
          glEnableVertexAttribArray(0);
          glEnableVertexAttribArray(1);
          glEnableVertexAttribArray(2);
          glEnableVertexAttribArray(3);
          /* Close vertax array */ 
          glBindVertexArray(0);
          }
          if (!T.I.empty())
          {
            /* Index data */
            glGenBuffers(1, &IBuf);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * T.I.size(), T.I.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            NumOfElements = (INT)T.I.size();
          }
          else
            NumOfElements = (INT)T.V.size();
        
        Type = T.Type;
        Mtl = Mat;
        Transform = matr().Identity();

        return *this;
      } /* End of 'Create' function */
    
    /* Load array of primitives from '*.G3DM' file function.
     * ARGUMENTS:
     *   - file name:
     *       const std::srting &FileName;
     * RETURNS:
     *   (std::vector<prim *>) result new primitives.
     */  
    // std::vector<prim *> LoadG3DM( const std::string &FileName );
    
    /* Free material function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID )
    {
      if (VA != 0)
      {
        /* Active vertex array */
        glBindVertexArray(VA);
        /* Unhook buffer */
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &VBuf);
        glBindVertexArray(0);
        glDeleteVertexArrays(1, &VA);
      }
      if (IBuf != 0)
        glDeleteBuffers(1, &IBuf);
    } /* End of 'Free' function */

  }; /* End of 'material' class */
  
  /* Primitives manager representation type */
  class primitive_manager : public resource_manager<prim>
  {
  public:
    /* Create primitive function.
     * ARGUMENTS:
     *   - topology base reference:
     *       const topology::base &Tpl;
     *   - material name for primitive:
     *       material *Mat;
     * RETURNS:
     *   (prim *) created primitive interface.
     */
    template<class vertex_type>
      prim * PrimCreate( material *Mat, const topology::base<vertex_type> &Tpl )
      {
        return resource_manager::Add(prim().Create(Mat, Tpl));
      } /* End of 'PrimCreate' function */
 
    /* Free primitive function.
     * ARGUMENTS:
     *   - primitive pointer:
     *       prim *Pr;
     * RETURNS: None.
     *   (prim *) created primitive interface.
     */
    VOID PrimFree( prim *Pr )
    {
      resource_manager::Delete(Pr);
    } /* End of 'PrimFree' function */
  }; /* End of 'primitive_manager' class */

} /* end of 'aggl' namespace */

#endif /* __primitives_h_ */

/* END OF 'primitives.h' FILE */
