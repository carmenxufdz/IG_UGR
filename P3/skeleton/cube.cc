#include "cube.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_cube::_cube(float Size)
{
    Vertices.resize(8);

    // Cara delantera
    Vertices[0]=_vertex3f(-Size/2,-Size/2,Size/2);
    Vertices[1]=_vertex3f(Size/2,-Size/2,Size/2);
    Vertices[2]=_vertex3f(Size/2,Size/2,Size/2);
    Vertices[3]=_vertex3f(-Size/2,Size/2,Size/2);

    // Cara trasera
    Vertices[4]=_vertex3f(-Size/2,-Size/2,-Size/2);
    Vertices[5]=_vertex3f(Size/2,-Size/2,-Size/2);
    Vertices[6]=_vertex3f(Size/2,Size/2,-Size/2);
    Vertices[7]=_vertex3f(-Size/2,Size/2,-Size/2);

    Edges.resize(12);

    Edges[0]=_vertex3ui(0,1);
    Edges[1]=_vertex3ui(0,3);
    Edges[2]=_vertex3ui(1,2);
    Edges[3]=_vertex3ui(2,3);
    Edges[4]=_vertex3ui(4,5);
    Edges[5]=_vertex3ui(4,7);
    Edges[6]=_vertex3ui(5,6);
    Edges[7]=_vertex3ui(6,7);
    Edges[8]=_vertex3ui(3,7);
    Edges[9]=_vertex3ui(0,4);
    Edges[10]=_vertex3ui(1,5);
    Edges[11]=_vertex3ui(2,6);

    Triangles.resize(12);

    // DIAGONAL IZQUIERDA, ABAJO AZUL
    Triangles[0]=_vertex3ui(2,3,1);
    Triangles[1]=_vertex3ui(0,1,3);
    Triangles[2]=_vertex3ui(6,2,5);
    Triangles[3]=_vertex3ui(1,5,2);
    Triangles[4]=_vertex3ui(7,6,4);
    Triangles[5]=_vertex3ui(5,4,6);
    Triangles[6]=_vertex3ui(3,7,0);
    Triangles[7]=_vertex3ui(4,0,7);
    Triangles[8]=_vertex3ui(6,7,2);
    Triangles[9]=_vertex3ui(3,2,7);
    Triangles[10]=_vertex3ui(1,0,5);
    Triangles[11]=_vertex3ui(4,5,0);

}
