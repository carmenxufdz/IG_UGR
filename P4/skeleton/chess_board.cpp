#include "chess_board.h"

_chess_board::_chess_board(float Size)
{

    //creacion de los vertices
    Vertices.resize(25);//5*5
    int n=0;//posicion del vertice

    //crea los vertices por fila (siendo cada fila (y) y cada columna (x))
    for(float y=-Size; y<=Size; y+=Size/2){//eje y
        for(float x=-Size; x<=Size; x+=Size/2){//eje x
            //cout << "N=" << n << ", X=" << x << ", Y=" << y << endl;
            Vertices[n]=_vertex3f(x,y,0);
            ++n;
        }
    }

    //creación de triangulos
    Triangles.resize(32);//4*4*2
    n=0;
    //16 + 2 (ESE 2 son el numero par de triangulos que pierde en total, ya que en cada vuelta pierde 1 triangulo, para pasar a la siguiente fila)
    for(int i=0; i<=18; ++i){
        //cout << "T" << n << ": P0=" << i << ", P1=" << (i+1) << ", P5=" << (i+5) << endl;
        Triangles[n]=_vertex3ui(i,(i+1),(i+5));
        ++n;
        //cout << "T" << n << ": P1=" << (i+1) << ", P6=" << (i+6) << ", P5=" << (i+5) << endl;
        Triangles[n]=_vertex3ui((i+1),(i+6),(i+5));
        ++n;

        //cout << (n) << " ---> " << (n%8) << endl;
        if((n%8)==0){
            ++i;
        }
    }

    //creación de mapeo de la textura
    //para ello convertimos las posiciones x e y en un sistema de coordenadas de mapeo
    Textura.resize(Triangles.size()*3);//el tamaño del array es el triple
    n=0;
    //indico la longitud maxima del tablero
    float max_x = Vertices[Vertices.size()-1].x*2;
    float max_y = Vertices[Vertices.size()-1].y*2;

    //transformo el sistemas de posiciones x, y en posiciones de coordenadas entre de 0 a 1
    //creando los triangulos de coordenadas para mapear la imagen sobre el tablero
    for(unsigned int i=0; i<Triangles.size(); ++i){

        Textura[n]=_vertex2f(0.5+Vertices[Triangles[i]._0].x/max_x,0.5+Vertices[Triangles[i]._0].y/max_y);
        Textura[n+1]=_vertex2f(0.5+Vertices[Triangles[i]._1].x/max_x,0.5+Vertices[Triangles[i]._1].y/max_y);
        Textura[n+2]=_vertex2f(0.5+Vertices[Triangles[i]._2].x/max_x,0.5+Vertices[Triangles[i]._2].y/max_y);
        n+=3;

    }
}
