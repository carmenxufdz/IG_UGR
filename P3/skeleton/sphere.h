#ifndef SPHERE_H
#define SPHERE_H

#include "object3dr.h"

class _sphere : public _object3Dr
{
public:
    _sphere(float Size=1.0, int divisiones=30);
};

#endif // SPHERE_H
