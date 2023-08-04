/*************************************************************
 * Copyright (C) 2023
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : def.h
 * PROGRAMMER  : AG2.
 * LAST UPDATE : 30.07.2023.
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Default common definition module.
 * NOTE        : Module namespace 'aggl'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#ifndef __def_h_
#define __def_h_
 
#include <cassert>
 
#ifndef WIN32
#define WIN32
#include <commondf.h>
#undef WIN32
#else
#include <commondf.h>
#endif /* WIN32 */
#define BOOL bool
 
/* Math support */
#include "mth/mth.h"
 
/* Debug memory allocation support */
#ifndef NDEBUG 
# define _CRTDBG_MAP_ALLOC
# include <crtdbg.h> 
# define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
static class __Dummy
{
public:
  /* Class constructor */
  __Dummy(VOID)
  {
    SetDbgMemHooks();
  } /* End of '__Dummy' constructor */
} __oops;
 
#endif /* _DEBUG */ 
 
#ifdef _DEBUG 
# ifdef _CRTDBG_MAP_ALLOC 
#   define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
# endif /* _CRTDBG_MAP_ALLOC */ 
#endif /* _DEBUG */
 
/* Base large integer types */
typedef unsigned long long UINT64;
typedef long long INT64;

/* OpenGL includes */
#define GLEW_STATIC
#include <glew.h>
#include <gl/gl.h>
#include <gl/glu.h>

#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")

#include <wglew.h>
#include <gl/wglext.h>

/* Project namespace */
namespace aggl
{
  /* Math types definitions */
  typedef mth::vec2<FLT> vec2;
  typedef mth::vec3<FLT> vec3;
  typedef mth::vec4<FLT> vec4;
  typedef mth::matr<FLT> matr;
  typedef mth::ray<FLT> ray;
  typedef mth::camera<FLT> camera;
} /* end of 'aggl' namespace */
 
#endif /* __def_h_ */
 
/* END OF 'def.h' FILE */
