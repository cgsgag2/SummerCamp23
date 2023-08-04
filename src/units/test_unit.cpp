/* FILE NAME   : test_unit.cpp
 * PROGRAMMER  : AG2
 * LAST UPDATE : 31.07.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Units samples module.
 *               Test unit for checking initialization of OpenGL.
 */

#include "aggl.h"

#include <vector>

/* Unit samples namespace */
namespace unit
{
  /* First test unit class */
  class test_unit : public aggl::unit
  {
  public:
    aggl::prim *Pr;

    /* Test unit default constructor */
    test_unit( aggl::anim *Ani )
    {
      aggl::vec3 Ka {1, 0, 0};
      aggl::vec3 Kd {0, 1, 0};
      aggl::vec3 Ks {0.5, 0.5, 0.5};
      FLT Ph = 30;
      // aggl::material_data MtlBulk {aggl::vec4(Ka), aggl::vec4(Kd), aggl::vec4(Ks, Ph)};
      
      aggl::material_pattern *MatPat = 
        Ani->MtlPatCreate("def", 0, "default");
      aggl::material *mtl = Ani->MtlCreate("CGSGFOREVER", Ka, Kd, Ks, Ph, 1, MatPat);

      std::vector<aggl::vertex::point> V {{aggl::vec3(0)}, {aggl::vec3(1, 0, 0)}, {aggl::vec3(0, 1, 0)}};
      std::vector<INT> I {0, 1, 2};
      aggl::topology::trimesh<aggl::vertex::point> Topo {V, I};
      Pr = Ani->PrimCreate(mtl, Topo);
    } /* End of 'test_unit' constructor */
    
    /* Test unit destructor */
    ~test_unit( VOID ) override
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
    } /* End of 'Response' function */
  }; /* End of 'test_unit' class */  
} /* end of 'unit' namespace */

static aggl::anim::unit_register<unit::test_unit> _("First test unit");

/* END OF 'test_unit.cpp' FILE */
