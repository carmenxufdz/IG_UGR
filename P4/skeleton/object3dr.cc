#include "object3dr.h"
#include <cmath>

void _object3Dr::create_triangles(int n_faces, int tam)
{

    int mod=n_faces*tam;
    int row=0;
    int face=0;
    Triangles.resize(mod*2);

    for(int i=0; i<mod; ++i)
    {
        if(face<n_faces)
            face++;
        else
        {
            row++;
            face=0;
        }

        Triangles[(i*2)]=_vertex3ui(((i*tam)+row+1)%mod,((i*tam)+row)%mod,(((i+1)*tam)+row)%mod);
        Triangles[(i*2)+1]=_vertex3ui((((i+1)*tam)+row)%mod,(((i+1)*tam)+row+1)%mod,((i*tam)+row+1)%mod);

    }
}

void _object3Dr::turns(int n_faces)
{
    // Gestión de las caras
    if(Vertices[0].y > Vertices[Vertices.size()-1].y)
    {
        vector<_vertex3f> aux;
        aux.clear();

        for(int i=0; i<Vertices.size(); i++)
        {
            aux.push_back(Vertices[Vertices.size()-1-i]);
        }


        for(int i=0; i<Vertices.size(); i++)
        {
            Vertices[i] = aux[i];
        }
    }

    //angulo de partida
    double ang_inicial = (2*M_PI)/n_faces;
    //calculo el nuevo angulo (angulo de referencia a sumar)
    double ang_mod = (2*M_PI)/n_faces;
    int tam = Vertices.size();
    int contador=0;
    for(int i=0; i<n_faces*tam; ++i){
        ++contador;

        Vertices.push_back(_vertex3f(Vertices[i%tam].x*cos(ang_inicial),//x_nueva = R * cos(angulo)
                                     Vertices[i%tam].y,// y_nueva = y
                                     Vertices[i%tam].x*(-sin(ang_inicial))));//z_nueva = R * sin(angulo));

        if(contador==tam){ // Se han incluido todos los puntos de una division
            //paso al siguiente angulo (siguiente división)
            ang_inicial+=ang_mod;
            contador=0;
        }
    }

    create_triangles(n_faces, tam);
}
