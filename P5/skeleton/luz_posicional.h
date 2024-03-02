#ifndef LUZ_POSICIONAL_H
#define LUZ_POSICIONAL_H

#include "luz.h"
#include <vector>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
using namespace std;

class _luz_posicional : public _luz
{
public:
    _luz_posicional(float posicion[3]);
    void activar();
    void desactivar();
    void moverLuzEjeX(int x);
};

#endif // LUZ_POSICIONAL_H
