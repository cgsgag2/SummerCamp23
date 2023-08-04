/* FILE NAME   : anim.h
 * PROGRAMMER  : AG2
 * LAST UPDATE : 30.07.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Animation system module.
 *               Animation handle module.
 */

#ifndef __anim_h_
#define __anim_h_

#include "def.h"

#include <iostream>
#include <map>

#include "stock/stock.h"

#include "rnd/render.h"
#include "input/input.h"
#include "input/timer.h"

/* Project namespace */
namespace aggl
{
  /* Forward unit class reference */
  class anim;

  /* Unit representation type */
  class unit
  {
  public:
    /* Unit default constructor */
    unit( VOID )
    {
    } /* End of 'unit' constructor */

    /* Unit virtual destructor */
    virtual ~unit( VOID )
    {
    } /* End of 'unit' destructor */

    /* Virtual render function.
     * ARGUMENTS:
     *   - animation context:
     *       anim *Ani;
     * RETURNS: None.
     */
    virtual VOID Render( anim *Ani )
    {
    } /* End of 'Render' function */

    /* Virtual response function.
     * ARGUMENTS:
     *   - animation context:
     *       anim *Ani;
     * RETURNS: None.
     */
    virtual VOID Response( anim *Ani )
    {
    } /* End of 'Response' function */
  }; /* End of 'unit' class */


  /* Animation representation type */
  class anim : public timer, public win, public input, public render
  {
  private:
    /* Single tone constructor for animation */
    anim( HINSTANCE hInst = GetModuleHandle(nullptr) ) : 
      timer(),
      win(hInst),
      input(win::hWnd, win::MouseWheel),
      render(win::hWnd)
    {
    } /* End of 'anim' constructor */
  
  public:
    /* Obtain animation system instance reference function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (anim &) Program reference to instance.
     */
    static anim & GetRef( VOID )
    {
      static anim Instance;
      return Instance;
    } /* End of 'GetRef' function */

    /* Obtain animation system instance pointer function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (anim *) Programm pointer to instance.
     */
    static anim * Get( VOID )
    {
      return &GetRef();
    } /* End of 'Get' function */

    /* Path to shader directory */
    std::string Path; 

    /*** Animation unit handle module ***/
    
  private:    
    /* Stock of units */
    stock<unit *> Units;
    
    /* Unit's names map */
    std::map<std::string, unit * (*)( VOID )> UnitsNames;

  public:
    /* Add new unit by name function.
     * ARGUMENTS:
     *   - reference to unit name:
     *       std::string &UnitName;
     * RETURNS: 
     *   (anim &) changed new stock.
     */
    anim & operator<<( const std::string &UnitName )
    {
      if (UnitsNames.find(UnitName) != UnitsNames.end())
      {
        unit *uni = UnitsNames[UnitName]();

        Units << uni;
      }
      return *this;
    } /* End of 'operator<<' function */

    /* Animation base destructor - delete all units */
    ~anim( VOID )
    {
      Units.Walk([]( unit *Uni )
      {
        delete Uni;
      });
    } /* End of '~anim' destructor */
    
    /* Unit auto registration representation type */
    template<typename unit_type>
      class unit_register
      {
      private:
        /* Create unit (static) function.
         * ARGUMENTS: None.
         * RETURNS:
         *   (unit *) Pointer to created unit.
         */
        static unit * Create( VOID )
        {
          static anim *Ani = anim::Get();
          return new unit_type(Ani);
        } /* End of 'Create' function */

      public:
        /* Unit register default constructor */
        unit_register( const std::string &UnitName )
        {
          anim::GetRef().UnitsNames[UnitName] = Create;
        } /* End of 'unit_register' constructor */
      }; /* End of 'unit_register' class */

    /*** Override virtual functions ***/
    VOID Run( VOID ) override;
    
  private:
    /* Animation render function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Render( VOID );

    BOOL OnCreate( CREATESTRUCT *CS ) override;
    VOID OnSize( UINT State, INT W, INT H ) override;
    VOID OnDestroy( VOID ) override;
    VOID OnTimer( INT Id ) override;
    BOOL OnEraseBkgnd( HDC hDC ) override;
    VOID OnPaint( HDC hDC, PAINTSTRUCT *Ps ) override;
    VOID OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys ) override;
    VOID OnButtonUp( INT X, INT Y, UINT Keys ) override;
    VOID OnMouseMove( INT X, INT Y, UINT Keys ) override;
    VOID OnMouseWheel( INT X, INT Y, INT Z, UINT Keys ) override;
    VOID OnExitSizeMove( VOID ) override;
    VOID OnEnterSizeMove( VOID ) override; 
    LRESULT OnMessage( UINT Msg, WPARAM wParam, LPARAM lParam ) override;
  }; /* End of 'anim' class */
  
} /* end of 'aggl' namespace */


#endif /* __anim_h_ */

/* END OF 'anim.h' FILE */
