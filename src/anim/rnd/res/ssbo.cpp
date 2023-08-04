/* FILE NAME   : ssbo.cpp
 * PROGRAMMER  : AG2
 * LAST UPDATE : 03.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               Shader Storage Buffer object (SSBO) module.
 */

#include "aggl.h"

aggl::ssbo & aggl::ssbo::Create( const std::string &SsboName, UINT BindPoints, INT NewSize, VOID *Bits )
{
  /* Setup OpenGL SSBO */
  glGenBuffers(1, &SSBOId);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBOId);
  glBufferData(GL_SHADER_STORAGE_BUFFER, NewSize, nullptr, GL_DYNAMIC_COPY);
  if (Bits != nullptr)
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, NewSize, Bits);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

  /* Add to stock */
  Size = NewSize;
  BindPoint = BindPoints;
  Name = SsboName;
  return *this;
} /* End of 'aggl::ssbo::Create' function */

/* SSBO data update function. 
 * ARGUMENTS:
 *   - SSBO number in stock: 
 *       INT SSBONo;
 *   - SSBO offset in bytes from block start: 
 *       INT BlocksOffset;
 *   - SSBO size in bytes: 
 *       INT BlocksOffset;
 *   - SSBO data: 
 *       VOID *Bits;
 * RETURNS: None. 
 */
VOID aggl::ssbo::Update( INT BlocksOffset, INT NewSize, VOID *Bits )
{
  /* Update SSBO data */
  if (BlocksOffset < 0)
    BlocksOffset = 0;
  if (BlocksOffset == 0 && NewSize == 0)
    NewSize = Size;
  if (BlocksOffset + NewSize >= Size)
    NewSize = Size - BlocksOffset;
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBOId);
  glBufferSubData(GL_SHADER_STORAGE_BUFFER, BlocksOffset, NewSize, Bits);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
} /* End of 'aggl::ssbo::Update' function */

/* SSBO apply function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID aggl::ssbo::Apply( VOID )
{
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BindPoint, SSBOId);
} /* End of 'aggl::ssbo::Apply' function */

/* Free SSBO function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID aggl::ssbo::Free( VOID )
{
} /* End of 'aggl::ssbo::Free' function */

/* END OF 'ssbo.cpp' FILE */
