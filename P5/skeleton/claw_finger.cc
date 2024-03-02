#include "claw_finger.h"
#include "colors.h"

using namespace _colors_ne;

_claw_finger::_claw_finger()
{
    paw = new _claw_paw();
}

void _claw_finger::draw(_mode_draw mode, _cube &cubo, _cone &cono)
{
    if(mode==FILL)
        glColor3fv((GLfloat *) &GREEN);
        //glColor3f(0.137255f, 0.419608f, 0.556863f);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(0.25,1.25,0.25);
    cubo.draw(mode);
    glPopMatrix();

    glPushMatrix() ;
    glTranslatef(0.09,-0.874,0) ;
    paw->draw(mode, cono) ;
    glPopMatrix() ;
}
