#include "claw_machine.h"
#include "colors.h"

using namespace _colors_ne;

_claw_machine::_claw_machine()
{
    base = new _claw_base();
}

void _claw_machine::draw(_mode_draw mode, _cube &cubo, _cone &cono, _cylinder &cilindro)
{
    if(mode==FILL)
        glColor3fv((GLfloat *) &BLUE);
        //glColor3f(0.137255f, 0.137255f, 0.556863f);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(7,1,7);
    cubo.draw(mode);
    glPopMatrix();

    // CAJA DE ABAJO
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,-17,0);
    glScalef(7,5,7);
    cubo.draw(mode);
    glPopMatrix();

    // PALOS QUE UNEN LAS CAJAS
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(3.25,-7.5,3.25);
    glScalef(0.5,14,0.5);
    cubo.draw(mode);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(3.25,-7.5,-3.25);
    glScalef(0.5,14,0.5);
    cubo.draw(mode);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(-3.25,-7.5,3.25);
    glScalef(0.5,14,0.5);
    cubo.draw(mode);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(-3.25,-7.5,-3.25);
    glScalef(0.5,14,0.5);
    cubo.draw(mode);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(eje_x,-0.75,eje_z);
    base->draw(mode, cubo, cono, cilindro);
    glPopMatrix();
}

void _claw_machine::moveClaw(bool close)
{
    base->moveClaw(close);
}

void _claw_machine::moveArm(bool up)
{
    base->moveArm(up);
}

void _claw_machine::RotateArm(bool giro)
{
    base->RotateArm(giro);
}

void _claw_machine::moveBaseX(bool izq)
{
    if(izq==true)
    {
        if(eje_x>-2.0)
            movX--;
    }
    else
    {
        if(eje_x<2.0)
            movX++;

    }
    eje_x=movX*0.05;
}

void _claw_machine::moveBaseZ(bool back)
{
    if(back==true)
    {
        if(eje_z>-2.0)
            movZ--;

    }
    else
    {
        if(eje_z<2.0)
                movZ++;

    }
    eje_z=movZ*0.05;

}

void _claw_machine::modMove(bool sum)
{
    base->modMove(sum);
}
void _claw_machine::modRot(bool sum)
{
    base->modRot(sum);
}

void _claw_machine::modMoveClaw(bool sum)
{
    base->modMoveClaw(sum);
}

float _claw_machine::getEjeX()
{
    return eje_x;
}

float _claw_machine::getEjeZ()
{
    return eje_z;
}

int _claw_machine::getRotate()
{
    return base->getRotate();
}

float _claw_machine::getAltura()
{
    return base->getAltura();
}

int _claw_machine::getGrado()
{
    return base->getGrado();
}

void _claw_machine::update()
{
    base->update();
}
