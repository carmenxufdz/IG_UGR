/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "basic_object3d.h"

typedef enum {PUNTO,LINE,FILL,CHESS} _mode_draw;
/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _object3D:public _wire_object3D
{
  public:
  vector<_vertex3ui> Triangles;

  void draw(_mode_draw mode);
  void draw_line();
  void draw_fill();
  void draw_chess();

};

#endif // OBJECT3D_H
