#ifndef CLAW_MACHINE_H
#define CLAW_MACHINE_H
#include "claw_base.h"
#include "cone.h"
#include "cylinder.h"
#include "cube.h"

class _claw_machine
{
private:
    _claw_base *base=nullptr;

    float eje_x=0.0;
    float eje_z=0.0;
    int movX=0;
    int movZ=0;
public:
    _claw_machine();
    void draw(_mode_draw mode, _cube &cubo, _cone &cono, _cylinder &cilindro);
    void moveClaw(bool close);

    void moveArm(bool up);
    void RotateArm(bool giro);
    void modMove(bool sum);
    void modRot(bool sum);
    void modMoveClaw(bool sum);

    void moveBaseX(bool izq);
    void moveBaseZ(bool back);

    float getEjeX();
    float getEjeZ();
    float getAltura();
    int getRotate();
    int getGrado();

    void update();
};

#endif // CLAW_MACHINE_H
