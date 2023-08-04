/* FILE NAME   : render.cpp
 * PROGRAMMER  : AG2
 * LAST UPDATE : 30.07.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Render system module.
 *               Render (*.cpp) file module.
 */

#include "aggl.h"

/* Render system initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID aggl::render::Init( VOID )
{
  INT i;
  PIXELFORMATDESCRIPTOR pfd = {0};
  UINT nums;
  HGLRC hRC;
  INT PixelAttribs[] =
  {
    WGL_DRAW_TO_WINDOW_ARB, TRUE,
    WGL_SUPPORT_OPENGL_ARB, TRUE,
    WGL_DOUBLE_BUFFER_ARB, TRUE,
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
    WGL_COLOR_BITS_ARB, 32,
    WGL_DEPTH_BITS_ARB, 32,
    0
  };
  INT ContextAttribs[] =
  {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
    WGL_CONTEXT_MINOR_VERSION_ARB, 6,
    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
                                  /* WGL_CONTEXT_CORE_PROFILE_BIT_ARB, */
    0
  };
  
  /* Prepare frame compatible device context */
  hDC = GetDC(hWnd);

  /* OpenGL init: pixel format setup */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(hDC, &pfd);
  DescribePixelFormat(hDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(hDC, i, &pfd);

  /* OpenGL init: rendering context setup */
  hGLRC = wglCreateContext(hDC);
  wglMakeCurrent(hDC, hGLRC);

  /* GLEW initialization */
  if (glewInit() != GLEW_OK)
  {
    IsInit = FALSE;
    exit(0);
  }
  /* Enable a new OpenGL profile support */
  wglChoosePixelFormatARB(hDC, PixelAttribs, nullptr, 1, &i, &nums);
  hRC = wglCreateContextAttribsARB(hDC, nullptr, ContextAttribs);
  
  wglMakeCurrent(nullptr, nullptr);
  wglDeleteContext(hGLRC);
  
  hGLRC = hRC;
  wglMakeCurrent(hDC, hGLRC);

  /* Setup OpenGL debug */
// #ifndef NDEBUG
//   OutputDebugString(glGetString(GL_VERSION));
//   OutputDebugString("\n");
//   OutputDebugString(glGetString(GL_VENDOR));
//   OutputDebugString("\n");
//   OutputDebugString(glGetString(GL_RENDERER));
//   OutputDebugString("\n");
// 
//   glEnable(GL_DEBUG_OUTPUT);
//   glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
//   glDebugMessageCallback(glDebugOutput, NULL);
//   glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE,
//     0, NULL, GL_TRUE);
// #endif /* NDEBUG */

  /* Render parameters setup */
  glClearColor(0.30, 0.47, 0.8, 1);
  glEnable(GL_DEPTH_TEST);
  
  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(-1);
  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  /* Set camera */
  Camera.ProjSize = 0.1;
  Camera.ProjDist = Camera.ProjSize;
  Camera.ProjFarClip = 3000;
  Camera.FrameW = 300;
  Camera.FrameH = 300;

  Camera.CamSet(vec3(5), vec3(0), vec3(0, 1, 0));
  PrimSSBO = anim::Get()->SSBOCreate("SSBO primitives", 2, sizeof(prim_data), nullptr);
  IsInit = TRUE;
} /* End of 'aggl::render::Init' function */

/* Render system close (deinitialization) function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID aggl::render::Close( VOID )
{
  wglMakeCurrent(nullptr, nullptr);
  wglDeleteContext(hGLRC);
  ReleaseDC(hWnd, hDC);
} /* End of 'aggl::render::Close' function */

/* Render system resize function.
 * ARGUMENTS:
 *   - window new size:
 *       INT NewW, INT NewH;
 * RETURNS: None.
 */
VOID aggl::render::Resize( INT NewW, INT NewH )
{
  /* Save size */
  Camera.FrameH = NewH;
  Camera.FrameW = NewW;
  /* Reset projection */
  Camera.ProjSet();

  glViewport(0, 0, NewW, NewH);
} /* End of 'aggl::render::Resize' function */
  
/* Start render frame function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID aggl::render::FrameStart( VOID )
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
} /* End of 'aggl::render::FrameStart' function */

/* Finish render frame function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID aggl::render::FrameEnd( VOID )
{
  glFinish();
  SwapBuffers(hDC);
} /* End of 'aggl::render::FrameEnd' function */

/* Primitive draw function.
 * ARGUMENTS:
 *   - primitive pointer:
 *       prim *Pr;
 *   - transformation matrix:
 *       const matr &World;
 * RETURNS: None.
 */
VOID aggl::render::Draw( const prim *Pr, const matr &World )
{
  matr 
    w = Pr->Transform * World,
    winw = w.Inverse().Transpose(),
    wp = Camera.MatrProj,
    wv = Camera.MatrView,
    wvp = w * Camera.MatrVP;
  
  // w = matr().RotateZ(45 * anim::Get()->Time);

  INT 
    RndProgId,
    gl_prim_type = Pr->Type == prim_type::LINES ? GL_LINES :
                   Pr->Type == prim_type::TRIMESH ? GL_TRIANGLES :
                   Pr->Type == prim_type::STRIP ? GL_TRIANGLE_STRIP :
                   GL_POINTS;
  Prim_data.MatrWVP = wvp;
  Prim_data.MatrW = w;
  Prim_data.MatrWInvTrans = winw;
  
  RndProgId = Pr->Mtl->Apply();
  
  if (RndProgId != 0)
  {
    // PrimSSBO->Update((INT)(&((prim_data *)0)->MatrWVP) / 16, 4, wvp.A[0]);
    PrimSSBO->Update(0, sizeof(prim_data), &Prim_data);
    PrimSSBO->Apply();
  }

  glBindVertexArray(Pr->VA);
  if (Pr->IBuf != 0)
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glDrawElements(gl_prim_type, Pr->NumOfElements, GL_UNSIGNED_INT, nullptr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
  else
    glDrawArrays(gl_prim_type, 0, Pr->NumOfElements);
  glBindVertexArray(0);
  glUseProgram(0);
} /* End of 'aggl::render::Draw' function */

/* END OF 'render.cpp' FILE */
