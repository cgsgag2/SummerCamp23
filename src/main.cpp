/* FILE NAME   : main.cpp
 * PROGRAMMER  : AG2
 * LAST UPDATE : 30.07.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Main project file.
 */

#include "aggl.h"

/* Get unique animation class */
// aggl::anim aggl::anim::Instance;
 
/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    CHAR *CmdLine, INT ShowCmd )
{
  /* Create console */
  // AllocConsole();
  // FILE *F = freopen("CONOUT$", "w", stdout);
  // system("@chcp 1251 > nul");
  // SetConsoleTitle("CGSG Summer camp 2023 Jr' Animation 3D project");

  aggl::anim *MyWindow = aggl::anim::Get();

  *MyWindow << "First test unit";

  // aggl::shader_manager shd;
  // aggl::shader *s = shd.ShaderCreate("default");

  // aggl::anim::GetRef().shader_manager::ShaderCreate();

  // MyWindow->MtlPatCreate("A", 0, "default");
  // MyWindow->MtlPatCreate("B", 1, "def");
  MyWindow->Run();

  // aggl::anim &MyWindow = aggl::anim::GetRef();
  // MyWindow.Run();
} /* End of 'WinMain' function */

/* END OF 'main.cpp' FILE */
