/* FILE NAME   : mtl_pattern.h
 * PROGRAMMER  : AG2
 * LAST UPDATE : 02.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               Material pattern and material pattern's manager handle module.
 */

#ifndef __mtl_pattern_h_
#define __mtl_pattern_h_

#include "def.h"

#include <iostream>

#include "shader.h"
#include "res_manager.h"

/* Project namespace */
namespace aggl
{
  /* Material pattern representation type */
  class material_pattern
  {
    friend class render;
  public:
    std::string Name; // Material pattern name
    INT AttribSize;   // Attribution size in bytes
    shader *Shd;      // Shader

    /* Material pattern default constructor */
    material_pattern( VOID )
    {
    } /* End of 'material_pattern' function */

    /* Material pattern constructor with parameters */
    // material_pattern( const std::string &MtlPatName, INT Attrib, const std::string &NewShdName = "default" );

    /* Material pattern creation function.
     * ARGUMENTS:
     *   - material pattern name:
     *       const std::string &MtlPatName;
     *   - attribution size:
     *       INT Attrib;
     *   - shader name:
     *       const std::string &NewShdName
     * RETURNS:
     *   (material_pattern &) self reference.
     */
    material_pattern & Create( const std::string &MtlPatName, INT Attrib, const std::string &NewShdName = "default" );
    
    /* Free material pattern function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID );

  }; /* End of 'material_pattern' class */
  
  /* Material_pattern manager representation type */
  class material_pattern_manager : public resource_manager<material_pattern, std::string>
  {
  public:
    /* Create material pattern function.
     * ARGUMENTS:
     *   - name of matelial pattern:
     *       const std::string &MtlPatName;
     *   - attribution size:
     *       INT Attrib;
     *   - shader prefix name:
     *       const std::string &ShdName;
     * RETURNS:
     *   (material_pattern *) created material pattern interface.
     */
    material_pattern * MtlPatCreate( const std::string &MtlPatName,
                                     INT Attrib,
                                     const std::string &ShdName )
    {
      return resource_manager::Add(material_pattern().Create(MtlPatName, Attrib, ShdName));
    } /* End of 'MtlPatCreate' function */

    /* Free material pattern function.
     * ARGUMENTS:
     *   - shader pointer:
     *       shader *Shd;
     * RETURNS: None.
     */
    VOID MtlPatFree( material_pattern *MtlPat )
    {
      resource_manager::Delete(MtlPat);
    } /* End of 'MtlPatFree' function */
  }; /* End of 'material_pattern_manager' class */

} /* end of 'aggl' namespace */

#endif /* __mtl_pattern_h_ */

/* END OF 'mtl_pattern.h' FILE */
