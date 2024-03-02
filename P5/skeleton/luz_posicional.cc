#include "luz_posicional.h"

_luz_posicional::_luz_posicional()
{
    this->posicion[0] = posicion[0];
    this->posicion[1] = posicion[1];
    this->posicion[2] = posicion[2];
}

void _luz_posicional::activar(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE );
    const GLfloat posf[4] = { posicion[0], posicion[1], posicion[2], 1.0 } ; // (x,y,z,w)
    glLightfv( GL_LIGHT0, GL_POSITION, posf );
}

void _luz_posicional::desactivar(){
    glDisable(GL_LIGHT0);
}

void _luz_posicional::moverLuzEjeX(int x){
    posicion[0]+=x;
    posicion[1]=3000;
    posicion[2]=5000;

    const GLfloat posf[4] = { x, 3000, 5000, 1.0 } ; // (x,y,z,w)
    glLightfv( GL_LIGHT0, GL_POSITION, posf );
}
