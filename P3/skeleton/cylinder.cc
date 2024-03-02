 #include "cylinder.h"

_cylinder::_cylinder(float Size, int divisiones)
{
    Vertices.resize(4);

    Vertices[0]=_vertex3f(0,-Size/2,0);
    Vertices[1]=_vertex3f(Size/2,-Size/2,0);
    Vertices[2]=_vertex3f(Size/2,Size/2,0);
    Vertices[3]=_vertex3f(0,Size/2,0);

    turns(divisiones);
}
