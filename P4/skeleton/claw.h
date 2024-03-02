#ifndef CLAW_H
#define CLAW_H
#include "claw_machine.h"
#include "sphere.h"
#include "cone.h"
#include "cylinder.h"
#include "cube.h"

class _claw
{
private:
    _sphere *esfera=nullptr;
    _cube *cubo=nullptr;
    _cylinder *cilindro=nullptr;
    _cone *cono=nullptr;

    _claw_machine *claw=nullptr;


    float rotate=0;
    float altura=-4.2;
    float eje_x=0.0;
    float eje_z=0.0;

    bool pick=false;
public:
    _claw();
    void draw(_mode_draw mode);

    void moveClaw(bool close);

    void moveArm(bool up);
    void RotateArm(bool giro);

    void modMove(bool sum);
    void modRot(bool sum);
    void modMoveClaw(bool sum);

    void moveBaseX(bool izq);
    void moveBaseZ(bool back);

    void moveBall();

    void update();

    void calculoNormal();


};

#endif // CLAW_H
