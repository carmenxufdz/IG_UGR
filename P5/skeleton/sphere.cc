#include "sphere.h"
#include <cmath>

_sphere::_sphere(float Size, int divisiones)
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

    turns(divisiones);
}

/*
void _sphere::calculoNormal()
{

    for(unsigned int i=0; i<Triangles.size(); ++i){
        // Compute the face normal
        _vertex3f vectorA = Vertices[Triangles[i]._1] - Vertices[Triangles[i]._0];
        _vertex3f vectorB = Vertices[Triangles[i]._2] - Vertices[Triangles[i]._0];
        _vertex3f normal = vectorA.cross_product(vectorB);


        NormalVertices[Triangles[i]._0] += normal;
        NormalVertices[Triangles[i]._1] += normal;
        NormalVertices[Triangles[i]._2] += normal;
    }


    for(unsigned int i=0; i<NormalVertices.size(); ++i){
        NormalVertices[i].normalize();
    }
}
*/

