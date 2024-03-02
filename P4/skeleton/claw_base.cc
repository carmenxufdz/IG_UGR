#include "claw_base.h"
#include "colors.h"

using namespace _colors_ne;

_claw_base::_claw_base()
{
    arm = new _claw_arm();
}
void _claw_base::draw(_mode_draw mode, _cube &cubo, _cone &cono, _cylinder &cilindro)
{
    if(mode==FILL)
        glColor3fv((GLfloat *) &MAGENTA);
        //glColor3f(0.184314f, 0.184314f, 0.309804f);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(0.5,0.5,0.5);
    cilindro.draw(mode);
    glPopMatrix();

    if(mode==FILL)
        glColor3fv((GLfloat *) &YEllOW);
        //glColor3f(0.560784f, 0.560784f, 0.737255f);

    glPushMatrix();
    glTranslatef(0,-2.25,0);
    glScalef(0.25,4,0.25);
    cilindro.draw(mode);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,altura,0);
    glRotatef(grado,0,1,0);
    arm->draw(mode, cubo, cono, cilindro);
    glPopMatrix();

}

void _claw_base::moveClaw(bool close)
{
    arm->moveClaw(close);
}

void _claw_base::moveArm(bool up)
{
    if(up==true)
    {
        if(altura<MAX_ALTURA)
            altura+=incH;
        if(altura>MAX_ALTURA)
            altura=MAX_ALTURA;
    }
    else
    {
        if(altura>MIN_ALTURA)
            altura-=incH;
        if(altura<MIN_ALTURA)
            altura=MIN_ALTURA;

    }


}

void _claw_base::RotateArm(bool giro)
{
    if(giro==true)
    {
        if(grado<MAX_GIRO)
            grado+=incG;
        if(grado>MAX_GIRO)
            grado=MAX_GIRO;
    }
    else
    {
        if(grado>MIN_GIRO)
            grado-=incG;
        if(grado<MIN_GIRO)
            grado=MIN_GIRO;

    }
}

void _claw_base::modMove(bool sum)
{
    if(sum==false){
        if(incH>0.1)
            incH-=0.1;
        if(incH<0.1)
            incH=0.1;
    }
    else{
        if(incH<1.0)
            incH+=0.1;
        if(incH>1.0)
            incH=1.0;
    }



}
void _claw_base::modRot(bool sum)
{
    if(sum==false){
        if(incG>1)
            incG--;
        if(incG<1)
            incG=1;
    }
    else{
        if(incG<5)
            incG++;
        if(incG>5)
            incG=5;
    }
}

void _claw_base::modMoveClaw(bool sum)
{
    arm->modMoveClaw(sum);
}

int _claw_base::getRotate()
{
    return grado;
}

float _claw_base::getAltura()
{
    return altura;
}

int _claw_base::getGrado()
{
    return arm->getGrado();
}

void _claw_base::update()
{

    if(arm->getGrado()>15 && arm->getGrado()<45 && altura!=MIN_ALTURA)
        arm->update(false);

    if(altura>MIN_ALTURA && arm->getGrado()==45)
        moveArm(false);

    else if(arm->getGrado()==15 && altura<MAX_ALTURA)
        moveArm(true);


    if(grado<MAX_GIRO && izq==false){
        RotateArm(true);
        if(grado==MAX_GIRO) izq=true;
    }
    else if(grado>MIN_GIRO && izq==true){
        RotateArm(false);
        if(grado==MIN_GIRO) izq=false;
    }

    if(altura==MIN_ALTURA)
        arm->update(true);
    else if(altura==MAX_ALTURA)
        arm->update(false);

}
