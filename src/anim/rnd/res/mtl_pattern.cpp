/* FILE NAME   : mtl_pattern.cpp
 * PROGRAMMER  : AG2
 * LAST UPDATE : 02.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               Material pattern module.
 */

#include "aggl.h"

/* Material pattern constructor with parameters */
// aggl::material_pattern::material_pattern( const std::string &MtlPatName, INT Attrib, const std::string &NewShdName) : 
//   Name(MtlPatName), AttribSize(Attrib)
// {
//   Shd = anim::Get()->ShaderCreate(NewShdName);
// } /* End of 'aggl::material_pattern::material_pattern' function */

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
aggl::material_pattern & aggl::material_pattern::Create( const std::string &MtlPatName, 
                                                         INT Attrib, 
                                                         const std::string &NewShdName )
{
  Name = MtlPatName;
  AttribSize = Attrib;
  Shd = anim::Get()->ShaderCreate(NewShdName);

  return *this;
} /* End of 'aggl::material_pattern::Create' function */

/* Free material pattern function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID aggl::material_pattern::Free( VOID )
{
  anim::Get()->ShaderFree(Shd);
} /* End of 'aggl::material_pattern::Free' function */

/* END OF 'mtl_pattern.cpp' FILE */
