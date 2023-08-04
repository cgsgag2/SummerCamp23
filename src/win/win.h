/* FILE NAME   : win.h
 * PROGRAMMER  : AG2
 * LAST UPDATE : 30.07.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Window handle module.
 */

#ifndef __win_h_
#define __win_h_

#include "def.h"

/* Project namespace */
namespace aggl
{
  /* Window representation type */
  class win
  {
  protected:
    HWND hWnd;           // Window handle
    INT W, H;            // Window size
    HINSTANCE hInstance; // Application handle
    INT MouseWheel;      // Mouse wheel parameter
  private:
    static LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg,
                                     WPARAM wParam, LPARAM lParam );
   
    BOOL IsFullScreen;
    RECT FullScreenSaveRect;
   
  public:
    BOOL IsActive;
   
    win( HINSTANCE hInst = GetModuleHandle(nullptr) );
    // virtual ~win( VOID );
   
    virtual VOID Run( VOID );
    // VOID FlipFullScreen( VOID );
    VOID CreateWin( VOID );
   
  private:
    // message cracks
    // VOID OnGetMinMaxInfo( MINMAXINFO *MinMax ); // ???
    virtual BOOL OnCreate( CREATESTRUCT *CS );
    virtual VOID OnDestroy( VOID );
    virtual BOOL OnEraseBkgnd( HDC hDC );
    virtual VOID OnPaint( HDC hDC, PAINTSTRUCT *Ps );
    virtual VOID OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized );
    virtual VOID OnMouseWheel( INT X, INT Y, INT Z, UINT Keys );
    virtual VOID OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys );
    virtual VOID OnButtonUp( INT X, INT Y, UINT Keys );
    virtual VOID OnMouseMove( INT X, INT Y, UINT Keys );
    virtual VOID OnSize( UINT State, INT W, INT H );
    virtual VOID OnTimer( INT Id );
    virtual VOID OnDropFiles( HDROP hDrop );
    virtual VOID OnDrawItem( INT Id, DRAWITEMSTRUCT *DrawItem );
    virtual LRESULT OnNotify( INT Id, NMHDR *NoteHead );
    virtual VOID OnCommand( INT Id, HWND hWndCtl, UINT CodeNotify );
    virtual VOID OnMenuSelect( HMENU hMenu, INT Item, HMENU hMenuPopup, UINT Flags);
    virtual VOID OnInitMenuPopup( HMENU hMenu, UINT Item, BOOL IsSystemMenu );
    virtual VOID OnHScroll( HWND hWndCtl, UINT Code, INT Pos );
    virtual VOID OnVScroll( HWND hWndCtl, UINT Code, INT Pos );
    virtual VOID OnExitSizeMove( VOID );
    virtual VOID OnEnterSizeMove( VOID );
    virtual LRESULT OnMessage( UINT Msg, WPARAM wParam, LPARAM lParam );
  }; /* End of 'win' class */
} /* end of 'aggl' namespace */

#endif /* __win_h_ */

/* END OF 'win.h' FILE */
