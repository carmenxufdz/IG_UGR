#include "claw_hand.h"
#include "colors.h"

using namespace _colors_ne;

_claw_hand::_claw_hand()
{
    finger = new _claw_finger();
}

void _claw_hand::draw(_mode_draw mode, _cube &cubo, _cone &cono)
{
    if(mode==FILL)
        glColor3fv((GLfloat *) &CYAN);
        //glColor3f(0.0f, 0.0f, 0.61f);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(2,0.25,0.25);
    cubo.draw(mode);
    glPopMatrix();

    // Pinza izquierda
    glPushMatrix();
    glTranslatef(-0.7875,-0.6125,0);
    glTranslatef(-0.125,0.75,0);
    glRotatef(-(grado),0,0,1);
    glTranslatef(0.125,-0.75,0);
    finger->draw(mode, cubo, cono);
    glPopMatrix();

    // Pinza derecha
    glPushMatrix();
    glTranslatef(0.7875,-0.6125,0);
    glTranslatef(0.125,0.75,0);
    glRotatef(grado,0,0,1);
    glTranslatef(-0.125,-0.75,0);
    glRotatef(180,0,1,0);
    finger->draw(mode, cubo, cono);
    glPopMatrix();

}

void _claw_hand::moveClaw(bool close)
{
    if(close==true){
        if(grado>MIN_APERTURA)
            grado-=incG;
        if(grado<MIN_APERTURA)
            grado=MIN_APERTURA;
    }
    else{
        if(grado<MAX_APERTURA)
            grado+=incG;
        if(grado>MAX_APERTURA)
            grado=MAX_APERTURA;
    }
}

void _claw_hand::modMoveClaw(bool sum)
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

int _claw_hand::getGrado()
{
    return grado;
}

void _claw_hand::update(bool cerrar)
{
    moveClaw(cerrar);
}
