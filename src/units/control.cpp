/* FILE NAME   : control.cpp
 * PROGRAMMER  : AG2
 * LAST UPDATE : 31.07.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Units samples module.
 *               Unit control module.
 */

#include "aggl.h"

#include <vector>

/* Unit samples namespace */
namespace unit
{
  /* Unit control representation type */
  class unit_ctrl : public aggl::unit
  {
  public:
    aggl::prim *Pr;     // Debug primitive
    aggl::vec3 CamLoc;  // Camera location
    aggl::vec3 CamDir;  // Camera direction

    /* Test unit default constructor */
    unit_ctrl( aggl::anim *Ani )
    {
      CamLoc = aggl::vec3(5);
    } /* End of 'test_unit' constructor */
    
    /* Test unit destructor */
    ~unit_ctrl( VOID ) override
    {
    } /* End of 'test_unit' constructor */
    
    /* Test unit render function.
     * ARGUMENTS:
     *   - animation context:
     *       aggl::anim *Ani;
     * RETURNS: None.
     */
    VOID Render( aggl::anim *Ani ) override
    {
      Ani->Draw(Pr, aggl::matr::RotateY(60 * Ani->Time));
      // srand(30);
      // glPointSize(8);
      // glRotated(0.01 * sin(Ani->Time), 1, 2, 3);
      // glBegin(GL_POINTS);
      // for (int i = 0; i < 300; i++)
      // {
      //   glColor3fv(aggl::vec3::Rnd0());
      //   glVertex3fv(aggl::vec3::Rnd1());
      // }
      // glEnd();
    } /* End of 'Render' function */

    /* test unit response function.
     * ARGUMENTS:
     *   - animation context:
     *       aggl::anim *Ani;
     * RETURNS: None.
     */
    VOID Response( aggl::anim *Ani ) override
    {
    }  
  }; /* End of 'unit_contrlo' class */  
} /* end of 'unit' namespace */

// static aggl::anim::unit_register<unit::test_unit> _("First test unit");

/* END OF 'test_unit.cpp' FILE */
