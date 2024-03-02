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

typedef enum {PUNTO,LINE,FILL,CHESS, FLAT, GOURAUD, TEXTURE, TEXTURE_FLAT, TEXTURE_GOURAUD} _mode_draw;
/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _object3D:public _wire_object3D
{
  public:
  vector<_vertex3f> NormalTriangulos;//guardo las normales de cada triangulo
  vector<_vertex3f> NormalVertices;//guardo las normales de cada vertice8

  void draw(_mode_draw mode);
  void draw_selection();
  void draw_line();
  void draw_fill();
  void draw_chess();
  void draw_flat();
  void draw_gouraud();
  void draw_textura();
  void draw_textura_flat();
  void draw_textura_gouraud();

  void calculoNormal();


};

#endif // OBJECT3D_H
