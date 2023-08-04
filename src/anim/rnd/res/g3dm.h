/* FILE NAME   : g3dm.h
 * PROGRAMMER  : AG2
 * LAST UPDATE : 04.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               Load 'G3DM' model handle module.
 */

#ifndef __g3dm_h_
#define __g3dm_h_

#include "def.h"

#include "anim/rnd/res/primitives.h"
#include "stock/stock.h"

/* Project namespace */
namespace aggl
{
  /* Unstructured data file reader class */
  class rdr
  {
  private:
    // Memory pointer reference
    BYTE *&Ptr;
  
  public:
    /* Class constructor.
      * ARGUMENTS:
      *   - reference to memory pointer:
      *       BYTE *&PtrRef;
      */
    rdr( BYTE *&PtrRef ) : Ptr(PtrRef)
    {
    } /* End of 'rdr' function */
  
    /* Read data function.
      * ARGUMENT:
      *   - read data pointer:
      *       type *Data;
      *   - read data count:
      *       INT Count;
      * RETURNS: None.
      */
    template<typename type>
      VOID operator()( type *Data, const INT Count = 1 )
      {
        if (Count == 1)
          *Data = *(type *)Ptr, Ptr += sizeof(type);
        else
          memcpy(Data, Ptr, sizeof(type) * Count), Ptr += sizeof(type) * Count;
      } /* End of 'operator()' function */
  }; /* End of 'rdr' class */

  /* G3DM representation type */
  class g3dm
  {
  private:
    stock<material *> Mtls;  // Materials from model

    matr Trans;
    DWORD 
      NumOfPrims,
      NumOfMaterials,
      NumOfTextures;
    stock<INT> 
      MtlNumbers,
      TexNumbers;
  public:
    stock<prim *> Prims;

    /* Load array of primitives from '*.G3DM' file function.
     * ARGUMENTS:
     *   - file name:
     *       const std::srting &FileName;
     * RETURNS: None.
     */  
    VOID LoadG3DM( const std::string &FileName );

    /* Draw '*.G3DM' model function.
     * ARGUMENTS:
     *   - transformation matrix:
     *       const matr &World;
     * RETURNS: None.
     */  
    VOID DrawG3DM( const matr &World );
    
    /* Free array of primitives from '*.G3DM' file function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */  
    VOID FreeG3DM( VOID )
    {
    } /* End of 'FreeG3DM' function */

  }; /* End of 'g3dm' class */
} /* end of 'aggl' namespace */

#endif /* __g3dm_h_ */

/* END OF 'g3dm.h' FILE */