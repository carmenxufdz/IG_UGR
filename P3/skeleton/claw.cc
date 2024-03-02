#include "claw.h"
#include <cmath>

using namespace _colors_ne;

_claw::_claw()
{
    cubo = new _cube();
    cilindro = new _cylinder();
    cono = new _cone(1,4);
    esfera = new _sphere();
    claw = new _claw_machine();

}

void _claw::draw(_mode_draw mode)
{

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,9.5,0);
    claw->draw(mode, *cubo, *cono, *cilindro);
    glPopMatrix();

    if(mode==FILL)
        glColor3fv((GLfloat *) &RED);
        //glColor3f(1.0f, 0.25f, 0.0f);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(eje_x,altura,eje_z);
    glRotatef(rotate,0,1,0);
    glScalef(1.5,1.5,1.5);
    esfera->draw(mode);
    glPopMatrix();

}

void _claw::moveClaw(bool close)
{
    claw->moveClaw(close);
}

void _claw::moveArm(bool up)
{
    claw->moveArm(up);
}

void _claw::RotateArm(bool giro)
{
    claw->RotateArm(giro);
}

void _claw::moveBaseX(bool izq)
{
    claw->moveBaseX(izq);
}

void _claw::moveBaseZ(bool back)
{
    claw->moveBaseZ(back);
}

void _claw::moveBall()
{
    float height=-4.0;
    int grado=15;

    if(claw->getEjeX()==eje_x && claw->getEjeZ()==eje_z && claw->getAltura()==height && claw->getGrado()==grado)
        this->pick=true;

    if(pick==true)
    {
        this->rotate=claw->getRotate();
        this->altura=claw->getAltura()-0.25;
        this->eje_x=claw->getEjeX();
        this->eje_z=claw->getEjeZ();
    }


    if(claw->getGrado()>grado)
    {
        pick=false;

        if(altura>-4.2){
            altura=altura-0.5;
            if(altura<-4.2)
                altura = -4.2;
        }
    }
}

void _claw::update()
{
    claw->update();
}

void _claw::modMove(bool sum)
{
    claw->modMove(sum);
}
void _claw::modRot(bool sum)
{
    claw->modRot(sum);
}

void _claw::modMoveClaw(bool sum)
{
    claw->modMoveClaw(sum);
}

