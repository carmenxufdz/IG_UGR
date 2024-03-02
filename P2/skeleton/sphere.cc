#include "sphere.h"
#include <cmath>

_sphere::_sphere(float Size)
{
    int tam=30;
    Vertices.clear();
    Vertices.resize(tam+1);

    float angulo=M_PI/tam;

    // Semicirculo
    for(int i=0; i<=tam; i++)
    {
        Vertices[i]=_vertex3f((-Size/2)*sin(angulo*i),(-Size/2)*cos(angulo*i),0);
    }
}
