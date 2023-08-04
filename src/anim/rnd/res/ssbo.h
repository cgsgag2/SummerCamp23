/* FILE NAME   : ssbo.h
 * PROGRAMMER  : AG2
 * LAST UPDATE : 02.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               Shader Storage Buffer object (SSBO) handle module.
 */

#ifndef __ssbo_h_
#define __ssbo_h_

#include "def.h"

#include <iostream>

/* Project namespace */
namespace aggl
{
  /* SSBO representation type */
  class ssbo
  {
    friend class render;
  public:
    std::string Name;  // SSBO name
    INT Size;          // SSBO number of 16 bytes block (16 - vec4((FLT)x, (FLT)y, (FLT)z, (FLT)w) : 4 * 4 = 16)
    UINT 
      SSBOId,          // OpenGL SSBO Id
      BindPoint;       // OpenGL SSBO bind point
    
    /* SSBO default constructor */
    ssbo( VOID )
    {
    } /* End of 'ssbo' function */

    /* Shader storage buffer object (SSBO) creation function.
     * ARGUMENTS:
     *   - SSBO name:
     *       const std::string &SsboName;
     *   - OpenGL SSBO bind point:
     *       UINT BindPoints;
     *   - SSBO size in bytes:
     *       INT NewSize;
     *   - pointer to SSBO data:
     *       VOID *Bits;
     * RETURNS:
     *   (ssbo &) self reference.
     */
    ssbo & Create( const std::string &SsboName, UINT BindPoints, 
                   INT NewSize, VOID *Bits );
        
    /* SSBO data update function.
     * ARGUMENTS:
     *   - SSBO offset 16 bytes blocks:
     *       INT BlocksOffset;
     *   - SSBO size in bytes:
     *       INT NewSize;
     *   - pointer to SSBO data:
     *       VOID *Bits;
     * RETURNS: None.
     */
    VOID Update( INT BlocksOffset, INT NewSize, VOID *Bits );
    
    /* SSBO apply function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Apply( VOID );

    /* Free SSBO function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID );

  }; /* End of 'ssbo' class */
  
  /* SSBO manager representation type */
  class ssbo_manager : public resource_manager<ssbo, std::string>
  {
  public:
    /* Shader storage buffer object function.
     * ARGUMENTS:
     *   - SSBO name:
     *       const std::string &SsboName;
     *   - OpenGL SSBO bind point:
     *       UINT BindPoints;
     *   - SSBO size in bytes:
     *       INT NewSize;
     *   - pointer to SSBO data:
     *       VOID *Bits;
     * RETURNS:
     *   (ssbo *) created SSBO interface.
     */
    ssbo * SSBOCreate( const std::string &SsboName, UINT BindPoints, 
                       INT NewSize, VOID *Bits )
    {
      return resource_manager::Add(ssbo().Create(SsboName, BindPoints, NewSize, Bits));
    } /* End of 'SSBOCreate' function */

    /* Free SSBO function.
     * ARGUMENTS:
     *   - SSBO pointer:
     *       ssbo *SSBuf;
     * RETURNS: None.
     */
    VOID SSBOFree( ssbo *SSBuf )
    {
      resource_manager::Delete(SSBuf);
    } /* End of 'SSBOFree' function */
  }; /* End of 'ssbo_manager' class */

} /* end of 'aggl' namespace */

#endif /* __ssbo_h_ */

/* END OF 'ssbo.h' FILE */
