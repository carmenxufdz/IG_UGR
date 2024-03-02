#ifndef CLAW_ARM_H
#define CLAW_ARM_H
#include "claw_hand.h"
#include "cone.h"
#include "cube.h"
#include "cylinder.h"

class _claw_arm
{
private:
    _claw_hand *hand=nullptr;

public:
    _claw_arm();
    void draw(_mode_draw mode, _cube &cubo, _cone &cono, _cylinder &cilindro);

    void moveClaw(bool close);
    void modMoveClaw(bool sum);

    int getGrado();

    void update(bool cerrar);
};

#endif // CLAW_ARM_H
