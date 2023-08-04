/* FILE NAME   : shader.h
 * PROGRAMMER  : AG2
 * LAST UPDATE : 01.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               Shaders and shader's manager handle module.
 */

#ifndef __shader_h_
#define __shader_h_

#include "def.h"

#include <fstream>

#include "res_manager.h"

/* Project namespace */
namespace aggl
{
  /* Shader representation type */
  class shader
  {
    friend class render;

  public:
    /* Shader filename */
    std::string Name;
    /* Shader program ID */
    INT ProgId;
    
    /* Shader default constructor */
    shader( VOID ) : Name {}, ProgId {}
    {
    } /* End of 'shader' function */

    /* Shader constructor by name of shader */
    shader( const std::string &ShdName ) : Name(ShdName), ProgId(0)
    {
    } /* End of 'shader' function */
 
    /* Save text to log file function.
     * ARGUMENTS:
     *   - text 1 to save:
     *       const std::string &Stage;
     *   - text 2 to save:
     *       const std::string &Text;
     * RETURNS: None.
     */
    VOID Log( const std::string &Stage, const std::string &Text );

    /* Text file load to memory function.
     * ARGUMENTS:
     *   - file name:
     *       const std::string &FileName;
     * RETURNS:
     *   (std::string) load text.
     */
    std::string LoadTextFile( const std::string &FileName );
    
    /* Load shader function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vigl::shader &) self reference.
     */
    shader & Load( VOID );

    /* Free shader function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID );

    /* Update shader function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Update( VOID );

  }; /* End of 'shader' class */
  
  /* Shader manager representation type */
  class shader_manager : public resource_manager<shader, std::string>
  {
  public:
    /* Create shader function.
     * ARGUMENTS:
     *   - name of shader:
     *       const std::string &ShdName;
     * RETURNS:
     *   (shader *) created shader interface.
     */
    shader * ShaderCreate( const std::string &ShdName )
    {
      return resource_manager::Add(shader(ShdName).Load());
    } /* End of 'ShaderCreate' function */

    /* Free shader function.
     * ARGUMENTS:
     *   - shader pointer:
     *       shader *Shd;
     * RETURNS: None.
     */
    VOID ShaderFree( shader *Shd )
    {
      resource_manager::Delete(Shd);
    } /* End of 'ShaderFree' function */
  }; /* End of 'shader_manager' class */

} /* end of 'aggl' namespace */

#endif /* __shader_h_ */

/* END OF 'shader.h' FILE */
