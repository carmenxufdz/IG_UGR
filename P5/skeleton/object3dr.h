#ifndef OBJECT3DR_H
#define OBJECT3DR_H

#include "object3d.h"

class _object3Dr : public _object3D
{
private:

public:
    void create_triangles(int n_faces, int tam);
    void turns(int n_faces);
};

#endif // OBJECT3DR_H
