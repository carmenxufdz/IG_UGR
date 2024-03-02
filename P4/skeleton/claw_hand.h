#ifndef CLAW_HAND_H
#define CLAW_HAND_H
#include "claw_finger.h"
#include "cube.h"
#include "cone.h"

class _claw_hand
{
private:
    _claw_finger *finger=nullptr;

    const int MAX_APERTURA=45;
    const int MIN_APERTURA=15;

    int incG=1;
    int grado=45;
public:
    _claw_hand();
    void draw(_mode_draw mode, _cube &cubo, _cone &cono);

    void moveClaw(bool close);
    void modMoveClaw(bool sum);

    int getGrado();

    void update(bool cerrar);
};

#endif // CLAW_HAND_H
