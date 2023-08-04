/* FILE NAME   : g3dm.cpp
 * PROGRAMMER  : AG2
 * LAST UPDATE : 03.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               Load 'G3DM' model module.
 */

#include "aggl.h"

#include <vector>

/* Load g3dm function.
 * ARGUMENTS:
 *    - load file name:
 *       std::string *FileName;
 * RETURNS: None.
 */
VOID aggl::g3dm::LoadG3DM( const std::string &FileName )
{
  /* Open file */
  std::fstream f(FileName, std::fstream::in | std::fstream::binary);
  DWORD sign;
  material_pattern *NewMtlPat = 
     anim::Get()->MtlPatCreate("G3DM material pattern", 0, "default");
  
  std::vector<topology::base<vertex::std>> Topos;
  std::vector<prim *> result;
  
  /* Obtain file length */
  f.seekg(0, std::fstream::end);
  INT flen = (INT)f.tellg();
  f.seekg(0, std::fstream::beg);
  
  std::vector<BYTE> mem;
  mem.resize(flen);
  BYTE *ptr = mem.data();

  f.read((CHAR *)mem.data(), flen);

  INT NumOfPrims;
  INT NumOfMaterials;
  INT NumOfTextures;
  rdr rd(ptr);

  rd(&sign);
  rd(&NumOfPrims);
  rd(&NumOfMaterials);
  rd(&NumOfTextures);

  if (sign != *(DWORD *)"G3DM")
    return;

  /* Load primitives */
  for (int i = 0; i < NumOfPrims; i++)
  {
    DWORD VN;
    DWORD IND;                /* Num of facets * 3 */
    DWORD MtlNo;              /* Material number in table below (in material section) */
    stock <vertex::std> V;    /* Vertex of g3dm */
    stock <INT> I;            /* Indexes of g3dm */

    rd(&VN);
    rd(&IND);
    rd(&MtlNo);

    for (int j = 0; j < VN; j++)
    {
      vertex::std vert;
      rd(&vert);
      V.push_back(vert);
    }

    for (int l = 0; l < IND; l++)
    {
      UINT ind;
      rd(&ind);
      I.push_back(ind);
    }

    MtlNumbers.push_back(MtlNo);

    topology::trimesh<vertex::std> Tpl(V, I);
    Topos.push_back(Tpl);
    result.push_back(anim::Get()->PrimCreate(nullptr, Tpl/*, MtlNo*/));  // MtlNo ???
  }

  /* Load materials */
  for (int k = 0; k < NumOfMaterials; k++)
  {
    struct
    {
      CHAR Name[300];         /* Material name */
      /* Illumination coefficients */
      vec3 Ka, Kd, Ks;        /* Ambient, diffuse, specular coefficients */
      FLT Ph;                 /* Phong power coefficient – shininess */
      FLT Trans;              /* Transparency factor */
      // DWORD Tex[8];           /* Texture references 
      //                          * (8 time: texture number in G3DM file, -1 if no texture) */
    } *fmat;
 
    rd(&fmat);
    
    Mtls.push_back(anim::Get()->MtlCreate(fmat->Name, fmat->Ka, fmat->Kd, fmat->Ks, fmat->Ph, fmat->Trans, NewMtlPat));
  }

  for (INT i = 0; i < NumOfPrims; i++)
  {
    result[i]->Mtl = Mtls[result[i]->MtlNo];
    Prims.push_back(result[i]);
  }

  Trans.Identity();

  f.close();
} /* End of 'aggl::g3dm::LoadG3DM' function */

/* Draw '*.G3DM' model function.
 * ARGUMENTS:
 *   - transformation matrix:
 *       const matr &World;
 * RETURNS: None.
 */  
VOID aggl::g3dm::DrawG3DM( const matr &World )
{
  matr A = Trans * World;

  for (int i = 0; i < NumOfPrims; i++)
    anim::Get()->Draw(Prims[i], A);
} /* End of 'aggl::g3dm::DrawG3DM' function */

// 
// VOID aggl::g3dm::LoadG3DM( const std::string &FileName )
// {
//   /* Open file */
//   std::fstream f(FileName, std::fstream::in | std::fstream::binary);
//   DWORD sign;
//   material_pattern *NewMtlPat = 
//      MtlPatCreate("G3DM material pattern", 0, "default");
// 
//   /* Obtain file length */
//   f.seekg(0, std::fstream::end);
//   INT flen = (INT)f.tellg();
//   f.seekg(0, std::fstream::beg);
//   
//   std::vector<BYTE> mem;
//   mem.resize(flen);
//   BYTE *ptr = mem.data();
// 
//   f.read((CHAR *)mem.data(), flen);
// 
//   INT NumOfPrims;
//   INT NumOfMaterials;
//   INT NumOfTextures;
//   rdr rd(ptr);
// 
//   rd(&sign);
//   rd(&NumOfPrims);
//   rd(&NumOfMaterials);
//   rd(&NumOfTextures);
// 
//   /* Load primitives */
//   for (int p = 0; p < NumOfPrims; p++)
//   {
//     DWORD NumOfVertexes;      /* Number of vertexes */
//     DWORD NumOfFacetIndexes;  /* Number of facets * 3 */
//     DWORD MtlNo;              /* Material number in table below (in material section) */
//     vertex::std *V;
//     INT *Ind;
//  
//     rd(&NumOfVertexes);
//     rd(&NumOfFacetIndexes);
//     rd(&MtlNo);
//  
//     rd(&V, NumOfVertexes);
//     rd(&Ind, NumOfFacetIndexes);
//  
//     // PrimCreate(nullptr, );
//     // AG2_RndPrimCreate(&Prs->Prims[p], AG2_RND_PRIM_TRIMESH, V, NumOfVertexes, Ind, NumOfFacetIndexes);
//     // Prs->Prims[p].MtlNo = AG2_RndMaterialsSize + MtlNo;
//   }
//  
//   /* Load materials */
//   for (int m = 0; m < NumOfMaterials; m++)
//   {
//     struct
//     {
//       CHAR Name[300];         /* Material name */
//       /* Illumination coefficients */
//       vec3 Ka, Kd, Ks;        /* Ambient, diffuse, specular coefficients */
//       FLT Ph;                 /* Phong power coefficient – shininess */
//       FLT Trans;              /* Transparency factor */
//       // DWORD Tex[8];           /* Texture references 
//       //                          * (8 time: texture number in G3DM file, -1 if no texture) */
//     } *fmat;
//  
//     rd(&fmat);
//     MtlCreate(fmat->Name, fmat->Ka, fmat->Kd, fmat->Ks, fmat->Ph, fmat->Trans, NewMtlPat);
//     
//     // for (t = 0; t < 8; t++)
//     //   mtl.Tex[t] = fmat->Tex[t] == -1 ? -1 : AG2_RndTexturesSize + fmat->Tex[t];
//     // mtl.ShdNo = AG2_RndShadersSize - 1;
//   }
//   return std::vector<prim *> {};
//   
//   // for (t = 0; t < NumOfTextures; t++)
//   // {
//   //   CHAR *Name;
//   //   DWORD W, H, C;
//   // 
//   //   Name = (CHAR *)ptr;
//   //   ptr += 300;
//   //   W = *(DWORD *)ptr;
//   //   ptr += 4;
//   //   H = *(DWORD *)ptr;
//   //   ptr += 4;
//   //   C = *(DWORD *)ptr;
//   //   ptr += 4;
//   //   AG2_RndTexAddImg(Name, W, H, C, ptr);
//   //   ptr += W * H * C;
//   // }
// } /* End of 'aggl::g3dm::LoadG3DM' function */

/* END OF 'g3dm.cpp' FILE */
