#ifndef PLY_H
#define PLY_H

#include "object3dr.h"
#include "file_ply_stl.h"

class _PLY_object3D : public _object3Dr
{
private:
    vector<float> coordinates;
    vector<unsigned int> positions;
public:
    _PLY_object3D(string file_name);
    _PLY_object3D(string file_name, int num);
};

#endif // PLY_H
