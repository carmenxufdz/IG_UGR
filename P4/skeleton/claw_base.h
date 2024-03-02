#ifndef CLAW_BASE_H
#define CLAW_BASE_H
#include "claw_arm.h"
#include "cube.h"
#include "cone.h"
#include "cylinder.h"

class _claw_base
{
private:
    _claw_arm *arm=nullptr;

    const int MAX_GIRO=180;
    const int MIN_GIRO=-180;

    const float MAX_ALTURA=1;
    const float MIN_ALTURA=-4;

    float incH=0.1;
    int incG=1;

    float altura=1;
    int grado=0;

    bool izq=false;
    bool sube=false;

public:
    _claw_base();
    void draw(_mode_draw mode, _cube &cubo, _cone &cono, _cylinder &cilindro);

    void moveClaw(bool close);

    void moveArm(bool up);
    void RotateArm(bool giro);
    void modMove(bool sum);
    void modRot(bool sum);
    void modMoveClaw(bool sum);

    float getAltura();
    int getRotate();
    int getGrado();

    void update();
};

#endif // CLAW_BASE_H
