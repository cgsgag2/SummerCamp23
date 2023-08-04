/* FILE NAME   : shader.cpp
 * PROGRAMMER  : AG2
 * LAST UPDATE : 01.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               Shaders and shader's manager module.
 */

#include "aggl.h"

#include <fstream>

/* Common includes to all shaders */
extern const CHAR CommonShaderIncludes[];

/* Save text to log file function.
 * ARGUMENTS:
 *   - text 1 to save:
 *       const std::string &Stage;
 *   - text 2 to save:
 *       const std::string &Text;
 * RETURNS: None.
 */
VOID aggl::shader::Log( const std::string &Stage, const std::string &Text )
{
  std::ofstream(anim::GetRef().Path + "/bin/shaders/~OP{S}30.LOG", std::ios_base::app) <<
    Name << "\n" << Stage << ":\n" << Text << "\n";
} /* End of 'aggl::shader::Log' function */

/* Text file load to memory function.
 * ARGUMENTS:
 *   - file name:
 *       const std::string &FileName;
 * RETURNS:
 *   (std::string) load text.
 */
std::string aggl::shader::LoadTextFile( const std::string &FileName )
{
  std::ifstream f(anim::GetRef().Path + FileName);
 
  return std::string((std::istreambuf_iterator<char>(f)),
                      std::istreambuf_iterator<char>());
} /* End of 'aggl::shader::LoadTextFile' function */

/* Load shader function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (vigl::shader &) self reference.
 */
aggl::shader & aggl::shader::Load( VOID )
{
  INT prg = 0, res;
  static CHAR Buf[30000];
  struct 
  {
    std::string Name;    // Shader name
    INT Type;            // Shader type
    // std::string Define;  // Defines for shader
    INT Id;                // Result shader Id
  } shds[] = 
  {
    {"vert", GL_VERTEX_SHADER}, 
    {"frag", GL_FRAGMENT_SHADER},
    {"geom", GL_GEOMETRY_SHADER},
    {"ctrl", GL_TESS_CONTROL_SHADER},
    {"eval", GL_TESS_EVALUATION_SHADER}
  };
  INT NoofS = sizeof(shds) / sizeof(shds[0]);
  BOOL isok = TRUE;
  
  for (int i = 0; i < NoofS && isok; i++)
  {
    /* Load text file */
    std::string txt = LoadTextFile("/bin/shaders/" + Name + "/" + shds[i].Name + ".glsl");
    if (txt.empty())
    {
      if (i >= 2)
        continue;
      Log(shds[i].Name, "Error load file");
      isok = FALSE;
      break;
    }
    /* Create shader */
    if ((shds[i].Id = glCreateShader(shds[i].Type)) == 0)
    {
      Log(shds[i].Name, "Error shader creation");
      isok = FALSE;
      break;
    }
    /* Attach text to shader */
    const CHAR *Src[] = {CommonShaderIncludes, txt.c_str()};
    glShaderSource(shds[i].Id, 2, Src, nullptr);

    /* Compile shader */
    glCompileShader(shds[i].Id);
    glGetShaderiv(shds[i].Id, GL_COMPILE_STATUS, &res);
    if (res != 1)
    {
      glGetShaderInfoLog(shds[i].Id, sizeof(Buf), &res, Buf);
      Log(shds[i].Name, Buf);
      isok = FALSE;
      break;
    }
  }
  /* Create shader program */
  if (isok)
    if ((prg = glCreateProgram()) == 0)
    {
      Log("PROG", "Error program creation");
      isok = FALSE;
    }
    else 
    {
      /* Attach shader to program */
      for (int i = 0; i < NoofS; i++)
        if (shds[i].Id != 0)
          glAttachShader(prg, shds[i].Id);
      /* Link shader program */
      glLinkProgram(prg);
      glGetProgramiv(prg, GL_LINK_STATUS, &res);
      if (res != 1)
      {
        glGetProgramInfoLog(prg, sizeof(Buf), &res, Buf);
        Log("PROG", Buf);
        isok = FALSE;
      }
    }
  /* Error in shader handle */
  if (!isok)
  {
    /* Delete shaders */
    for (int i = 0; i < NoofS; i++)
      if (shds[i].Id != 0)
      {
        if (prg != 0)
          glDetachShader(prg, shds[i].Id);
        glDeleteShader(shds[i].Id);
      }
    /* Delete program */
    if (prg != 0)
      glDeleteProgram(prg);
    prg = 0;
  }
  ProgId = prg;
  return *this;
} /* End of 'aggl::shader::Load' function */

/* Free shader function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID aggl::shader::Free( VOID )
{
  UINT shds[5] = {0};
  INT n;

  if (ProgId == 0 || !glIsProgram(ProgId))
    return;
  glGetAttachedShaders(ProgId, 5, &n, shds);
  /* Delete shaders */
  for (int i = 0; i < n; i++)
    if (shds[i] != 0 && glIsShader(shds[i]))
    {
      glDetachShader(ProgId, shds[i]);
      glDeleteShader(shds[i]);
    }
  /* Delete program */
  glDeleteProgram(ProgId);
} /* End of 'aggl::shader::Free' function */

/* Update shader function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID aggl::shader::Update( VOID )
{
} /* End of 'aggl::shader::Update' function */

static const CHAR CommonShaderIncludes[] =
R"separator(
 
#version 460
/* 
layout(std140, binding = 0) buffer Camera
{
  mat4 MatrView;
  mat4 MatrProj;
  mat4 MatrVP;
  vec4 CamLocFrameW;
  vec4 CamDirProjDist;
  vec4 CamRightWp;
  vec4 CamUpHp;
  vec4 CamAtFrameH;
};

layout(std140, binding = 1) buffer Syncronization
{
  vec4 SyncGlobalTimeGlobalDeltaTimeTimeDeltaTime;
};
*/ 
layout(std140, binding = 2) buffer prim_data
{
  mat4 MatrWVP;
  mat4 MatrW;
  mat4 MatrWInvTrans;
  // vec4 RndIsWireIsAny;
  // bool TextureFlags[8];
};
 
layout(std140, binding = 3) buffer material_data 
{
  vec4 Ka4;
  vec4 KdTrans;
  vec4 KsPh;
};
  
#define Ka Ka4.xyz
#define Kd KdTrans.xyz
#define Trans KdTrans.w
#define Ks KsPh.xyz
#define Ph KsPh.w
 
)separator";

/* END OF 'shader.cpp' FILE */
