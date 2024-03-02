#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>
#include <GL/gl.h>
#include "colors.h"
#include "vertex.h"

// TURQUESA
const _vertex4f AMBIENTE_TURQUESA(0.1, 0.18725, 0.1745, 0.8);
const _vertex4f DIFUSA_TURQUESA(0.396, 0.74151, 0.69102, 0.8);
const _vertex4f ESPECULAR_TURQUESA(0.297254, 0.30829, 0.306678, 0.8);
const float BRILLO_TURQUESA = 12.8;

// PERLADO
const _vertex4f AMBIENTE_PERLADO(0.25, 0.20725, 0.20725, 0.922);
const _vertex4f DIFUSA_PERLADO(1, 0.829, 0.829, 0.922);
const _vertex4f ESPECULAR_PERLADO(0.296648, 0.296648, 0.296648, 0.922);
const float BRILLO_PERLADO = 11.264;

// OBSIDIANA
const _vertex4f AMBIENTE_OBSIDIANA(0.05375, 0.05, 0.06625, 0.82);
const _vertex4f DIFUSA_OBSIDIANA(0.18275, 0.17, 0.22525, 0.8);
const _vertex4f ESPECULAR_OBSIDIANA(0.332741, 0.328634, 0.346435, 0.82);
const float BRILLO_OBSIDIANA = 30;

// JADE
const _vertex4f AMBIENTE_ESMERALDA(0.0215, 0.1745, 0.0215, 0.55);
const _vertex4f DIFUSA_ESMERALDA(0.07568, 0.61424, 0.07568, 0.55);
const _vertex4f ESPECULAR_ESMERALDA(0.633, 0.727811, 0.633, 0.55);
const float BRILLO_ESMERALDA = 100;

// RUBI
const _vertex4f AMBIENTE_RUBI(0.1745, 0.01175, 0.01175, 0.55);
const _vertex4f DIFUSA_RUBI(0.61424, 0.04136, 0.04136, 0.55);
const _vertex4f ESPECULAR_RUBI(0.727811, 0.626959, 0.626959, 0.55);
const float BRILLO_RUBI = 76.8;


// BASE
const _vertex4f AMBIENTE(0.2, 0.2, 0.2, 1.0);
const _vertex4f DIFUSA(0.8, 0.8, 0.8, 1.0);
const _vertex4f ESPECULAR(0, 0, 0, 1);
const float BRILLO = 0;

#endif // MATERIAL_H
