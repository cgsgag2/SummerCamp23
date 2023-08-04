/* FILE NAME   : material.h
 * PROGRAMMER  : AG2
 * LAST UPDATE : 02.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               Material's and material's manager handle module.
 */

#ifndef __material_h_
#define __material_h_

#include "def.h"

#include "mtl_pattern.h"
#include "ssbo.h"

#include <iostream>

/* Project namespace */
namespace aggl
{
  /* Material data representation type */
  struct material_data
  {
    vec4 Ka4;      // Ambient
    vec4 KdTrans;  // Diffuse + transparency
    vec4 KsPh;     // Specular + phong coefficient
  }; /* End of 'material_data' struct */

  /* Material representation type */
  class material
  {
    friend class render;
  public:
    std::string Name;          // Material name
    material_pattern *MtlPat;  // pointer to material pattern 
    ssbo *MtlSSBO;             // Shader storage buffer object
    // Add later textures and ssbo

    /* Material default constructor */
    material( VOID )
    {
    } /* End of 'material' function */

    /* Material creation function.
     * ARGUMENTS:
     *   - material name:
     *       const std::string &MtlName;
     *   - ambient coefficient:
     *       vec3 Ka;
     *   - diffuse coefficient:
     *       vec3 Kd;
     *   - specular coefficient:
     *       vec3 Ks;
     *   - Phong coefficient - shiness:
     *       FLT Ph;
     *   - transparency factor:
     *       FLT Trans;
     *   - pointer to material pattern:
     *       material_pattern *NewMtlPat;
     * RETURNS:
     *   (material &) self reference.
     */
    // material & Create( const std::string &MtlName, material_data *MtlData, material_pattern *NewMtlPat );
    material & Create( const std::string &MtlName, const vec3 &Ka, const vec3 &Kd, const vec3 &Ks, 
                       FLT Ph, FLT Trans, material_pattern *NewMtlPat );
    
    /* Apply material function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (INT) new shader stock number.
     */
    INT Apply( VOID );
    
    /* Free material function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID );

  }; /* End of 'material' class */
  
  /* Material manager representation type */
  class material_manager : public resource_manager<material, std::string>
  {
  public:
    /* Create material function.
     * ARGUMENTS:
     *   - name of matelial:
     *       const std::string &MtlName;
     *   - ambient coefficient:
     *       vec3 Ka;
     *   - diffuse coefficient:
     *       vec3 Kd;
     *   - specular coefficient:
     *       vec3 Ks;
     *   - Phong coefficient - shiness:
     *       FLT Ph;
     *   - transparency factor:
     *       FLT Trans;
     *       material_pattern *NewMtlPat;
     * RETURNS:
     *   (material *) created material interface.
     */
    material * MtlCreate( const std::string &MtlName, const vec3 &Ka, const vec3 &Kd, const vec3 &Ks, 
                          FLT Ph, FLT Trans, material_pattern *NewMtlPat )
    {
      return resource_manager::Add(material().Create(MtlName, Ka, Kd, Ks, Ph, Trans, NewMtlPat));
    } /* End of 'MtlPatCreate' function */

    /* Free material function.
     * ARGUMENTS:
     *   - material pointer:
     *       material *Mtl;
     * RETURNS: None.
     */
    VOID MtlFree( material *Mtl )
    {
      resource_manager::Delete(Mtl);
    } /* End of 'MtlFree' function */
  }; /* End of 'material_manager' class */

} /* end of 'aggl' namespace */

#endif /* __material_h_ */

/* END OF 'material.h' FILE */
