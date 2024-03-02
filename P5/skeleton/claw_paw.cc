#include "claw_paw.h"
#include <cmath>
#include "colors.h"

using namespace _colors_ne;

_claw_paw::_claw_paw()
{
}

void _claw_paw::draw(_mode_draw mode, _cone &cono)
{
    if(mode==FILL)
        glColor3fv((GLfloat *) &RED);
        //glColor3f(0.560784f, 0.560784f, 0.737255f);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(-0.5,0,0);
    glRotatef(40,0,0,1);
    glTranslatef(0.5,0,0);
    glRotatef(45,0,1,0);
    glRotatef(180,1,0,0);
    glScalef (0.35,1,0.35);
    glTranslatef(0,0.5,0);
    cono.draw(mode);
    glPopMatrix();
}
