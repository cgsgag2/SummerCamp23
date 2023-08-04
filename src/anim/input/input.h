/* FILE NAME   : input.h
 * PROGRAMMER  : AG2
 * LAST UPDATE : 30.07.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Animation input system module.
 *               Input handle module.
 */

#ifndef __input_h_
#define __input_h_

#include "def.h"

/* Project namespace */
namespace aggl
{
  /* Keyboard representation type */
  class keyboard
  {
  }; /* End of 'keyboard' class */

  /* Mouse representaion type */
  class mouse
  {
  private:
    HWND &hWnd;  // Window handle
    INT &Wheel;  // Mouse wheel parameter

  public:
    // INT Dz;
    
    /* Mouse default constructor */
    mouse( HWND &hWndRef, INT &WheelRef ) : hWnd(hWndRef), Wheel(WheelRef)
    {
    }
  }; /* End of 'mouse' class */

  /* Joystick representation type */
  class joystick
  {
  }; /* End of 'joystick' class */

  /* Input system representation type */
  class input : public keyboard, public mouse, public joystick
  {
  public:
    /* Input system default constructor */
    input( HWND &hWndRef, INT &WheelRef ) : mouse(hWndRef, WheelRef)
    {
    }
  }; /* End of 'input' class */
  
} /* end of 'aggl' namespace */


#endif /* __input_h_ */

/* END OF 'input.h' FILE */
