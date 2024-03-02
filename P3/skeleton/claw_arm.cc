#include "claw_arm.h"
#include "colors.h"

using namespace _colors_ne;

_claw_arm::_claw_arm()
{
    hand = new _claw_hand();
}

void _claw_arm::draw(_mode_draw mode, _cube &cubo, _cone &cono, _cylinder &cilindro)
{
    if(mode==FILL)
        glColor3fv((GLfloat *) &YEllOW);
        //glColor3f(0.560784f, 0.560784f, 0.737255f);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,-3.5,0);
    glScalef(0.25,7,0.25);
    cilindro.draw(mode);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-7,0);
    hand->draw(mode,cubo, cono);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-7,0);
    glRotatef(90,0,1,0);
    hand->draw(mode, cubo, cono);
    glPopMatrix();

}

void _claw_arm::moveClaw(bool close)
{
    hand->moveClaw(close);
}

void _claw_arm::modMoveClaw(bool sum)
{
    hand->modMoveClaw(sum);
}

int _claw_arm::getGrado()
{
    return hand->getGrado();
}

void _claw_arm::update(bool cerrar)
{
    hand->update(cerrar);
}
