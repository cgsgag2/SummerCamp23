/* FILE NAME   : material.cpp
 * PROGRAMMER  : AG2
 * LAST UPDATE : 02.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               Material module.
 */

#include "aggl.h"

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
 *       material_pattern *NewNamePat;
 * RETURNS:
 *   (material &) self reference.
 */
aggl::material & aggl::material::Create( const std::string &MtlName, const vec3 &Ka, const vec3 &Kd, const vec3 &Ks, 
                                         FLT Ph, FLT Trans, material_pattern *NewMtlPat )
{
  Name = MtlName;
  MtlPat = NewMtlPat;
  material_data MtlData;
  MtlData.Ka4 = vec4(Ka);
  MtlData.KdTrans = vec4(Kd, Trans);
  MtlData.KsPh = vec4(Ks, Ph);
  MtlSSBO = anim::Get()->SSBOCreate("SSBO Material", 3, sizeof(material_data), &MtlData);
  MtlSSBO->Apply();
  
  return *this;
} /* End of 'aggl::material::Create' function */

/* Apply material function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (INT) new shader stock number.
 */
INT aggl::material::Apply( VOID )
{
  INT prg = MtlPat->Shd->ProgId;

  glUseProgram(prg);
  if (prg == 0)
    return 0;
  
  // ????
  MtlSSBO->Apply();
  /*
  * SSBO
  * Textures
  */
  return prg;
} /* End of 'aggl::material::Apply' function */

/* Free material function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID aggl::material::Free( VOID )
{
} /* End of 'aggl::material::Free' function */

/* END OF 'material.cpp' FILE */

