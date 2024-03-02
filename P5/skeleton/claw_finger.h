#ifndef CLAW_FINGER_H
#define CLAW_FINGER_H
#include "claw_paw.h"
#include "cube.h"
#include "cone.h"

class _claw_finger
{
private:
    _claw_paw *paw=nullptr;

public:
    _claw_finger();
    void draw(_mode_draw mode, _cube &cubo, _cone &cono);
};

#endif // CLAW_FINGER_H
