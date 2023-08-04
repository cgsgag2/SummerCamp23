/* FILE NAME   : anim.cpp
 * PROGRAMMER  : AG2
 * LAST UPDATE : 30.07.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Animation system module.
 *               Animation module file.
 */

#include "aggl.h"

/* Help class for animation start */
static class anim_start
{
public:
  /* Animation start default constructor */
  anim_start( VOID )
  {
    aggl::anim::Get()->CreateWin();
    CHAR Buf[_MAX_PATH];
    GetCurrentDirectory(sizeof(Buf), Buf);
    aggl::anim::GetRef().Path = Buf;
  } /* End of 'anim_start' constructor */
} __startanim; /* End of 'anim_start' class */
 
/* Animation render function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID aggl::anim::Render( VOID )
{
  /* */
  timer::Response();

  Units.Walk([this]( unit *Uni )
  {
    Uni->Response(this);
  });
  /* ... */
  render::FrameStart();
  Units.Walk([this]( unit *Uni )
  {
    Uni->Render(this);
  });
  render::FrameEnd();
} /* End of 'aggl::anim::Render' function */
 
/*** Message Crackers ***/

/* Window message loop function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID aggl::anim::Run( VOID )
{
  MSG msg;
  
  while (TRUE)
  {
    /* Check message at window message queue */
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
      if (msg.message == WM_QUIT)
        break;
      else
      {
        /* Displatch message to window */
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    else
    {
      // SendMessage(anim::win::hWnd, WM_TIMER, 47, 0);
      if (IsInit)
        Render();
      /* Idle... */
    }
  }
} /* End of 'aggl::anim::Run' function */

/* WM_CREATE window message handle function.
 * ARGUMENTS:
 *   - structure with creation data:
 *       CREATESTRUCT *CS;
 * RETURNS:
 *   (BOOL) TRUE to continue creation window, FALSE to terminate.
 */
BOOL aggl::anim::OnCreate( CREATESTRUCT *CS )
{
  SetTimer(win::hWnd, 30, 2, nullptr);
  render::Init();

  return TRUE;
} /* End of 'aggl::anim::OnCreate' function */

/* WM_SIZE window message handle function.
 * ARGUMENTS:
 *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
 *       UINT State;
 *   - new width and height of client area:
 *       INT W, H;
 * RETURNS: None.
 */
VOID aggl::anim::OnSize( UINT State, INT W, INT H )
{
  // SRender();
  render::Resize(W, H);
} /* End of 'aggl::anim::OnSize' function */

/* WM_DESTROY window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID aggl::anim::OnDestroy( VOID )
{
  render::Close();
} /* End of 'aggl::anim::OnDestroy' function */

/* WM_TIMER window message handle function.
 * ARGUMENTS:
 *   - specified the timer identifier.
 *       INT Id;
 * RETURNS: None.
 */
VOID aggl::anim::OnTimer( INT Id ) 
{
  if (IsInit)
    Render();
} /* End of 'aggl::anim::OnTimer' function */

/* WM_ERASEBKGND window message handle function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS:
 *   (BOOL) TRUE if background is erased, FALSE otherwise.
 */
BOOL aggl::anim::OnEraseBkgnd( HDC hDC )
{
  return TRUE;
} /* End of 'aggl::anim::OnEraseBkgnd' function */

/* WM_PAINT window message handle function.
 * ARGUMENTS:
 *   - window device context:
 *       HDC hDC;
 *   - paint message structure pointer:
 *       PAINTSTRUCT *PS;
 * RETURNS: None.
 */
VOID aggl::anim::OnPaint( HDC hDC, PAINTSTRUCT *PS )
{
  if (IsInit)
    Render();
} /* End of 'aggl::anim::OnPaint' function */ 

/* WM_MOUSEWHEEL window message handle function.
 * ARGUMENTS:
 *   - mouse window position:
 *       INT X, Y;
 *   - mouse wheel relative delta value:
 *       INT Z;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys;
 * RETURNS: None.
 */
VOID aggl::anim::OnMouseWheel( INT X, INT Y, INT Z, UINT Keys )
{
  // MouseWheel += Z;
} /* End of 'win::OnMouseWheel' function */

/* Button down of mouse window message handle function.
 * ARGUMENTS:
 *   - flag for double click on mouse:
 *       BOOL IsDoubleClick;
 *   - coordinates of mouse:
 *       INT X, INT Y;
 *   - pressed keys: 
 *       UINT Keys;
 * RETURNS: None.
 */
VOID aggl::anim::OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys )
{
} /* End of 'aggl::anim::OnButtonDown' function */

/* Button up of mouse window message handle function.
 * ARGUMENTS:
 *   - coordinates of mouse:
 *       INT X, INT Y;
 *   - pressed keys: 
 *       UINT Keys;
 * RETURNS: None.
 */
VOID aggl::anim::OnButtonUp( INT X, INT Y, UINT Keys )
{
} /* End of 'aggl::anim::OnButtonUp' function */

/* Move mouse window message handle function.
 * ARGUMENTS:
 *   - coordinates of mouse:
 *       INT X, INT Y;
 *   - pressed keys: 
 *       UINT Keys;
 * RETURNS: None.
 */
VOID aggl::anim::OnMouseMove( INT X, INT Y, UINT Keys )
{
} /* End of 'aggl::anim::OnMouseMove' function */

/* WM_EXITSIZEMOVE window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID aggl::anim::OnExitSizeMove( VOID )
{
} /* End of 'aggl::anim::OnExitSizeMove' function */
 
/* WM_ENTERSIZEMOVE window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID aggl::anim::OnEnterSizeMove( VOID )
{
} /* End of 'aggl::anim::OnEnterSizeMove' function */

/* Window message universal handle function.
 * Should be returned 'DefWindowProc' call result.
 * ARGUMENTS:
 *   - message type (see WM_***):
 *      UINT Msg;
 *   - message 'word' parameter:
 *      WPARAM wParam;
 *   - message 'long' parameter:
 *      LPARAM lParam;
 * RETURNS:
 *   (LRESULT) message depende return value.
 */
LRESULT aggl::anim::OnMessage( UINT Msg, WPARAM wParam, LPARAM lParam )
{
  switch (Msg)
  {
  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      DestroyWindow(win::hWnd);
    return 0;
  }
  
  return DefWindowProc(win::hWnd, Msg, wParam, lParam);
} /* End of 'win::OnMessage' function */


/* END OF 'anim.cpp' FILE */
