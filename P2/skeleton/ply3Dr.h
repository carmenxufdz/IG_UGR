#ifndef PLY3DR_H
#define PLY3DR_H

#include "object3dr.h"

class _PLY_object3Dr : public _object3Dr
{
private:
    vector<float> coordinates;
    vector<unsigned int> positions;
public:
    _PLY_object3Dr(string file_name, int n);
};

#endif // PLY3DR_H
