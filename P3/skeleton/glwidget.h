/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/gl.h>
#include <QWindow>
#include <QOpenGLWidget>
#include <QTimer>
#include <QKeyEvent>
#include <iostream>
#include "vertex.h"
#include "colors.h"
#include "axis.h"

#include "tetrahedron.h"
#include "cube.h"
#include "cone.h"
#include "cylinder.h"
#include "sphere.h"
#include "ply.h"

#include "claw.h"
#include "claw_arm.h"
#include "claw_base.h"
#include "claw_finger.h"
#include "claw_hand.h"
#include "claw_machine.h"
#include "claw_paw.h"

namespace _gl_widget_ne {

  const float X_MIN=-.1;
  const float X_MAX=.1;
  const float Y_MIN=-.1;
  const float Y_MAX=.1;
  const float FRONT_PLANE_PERSPECTIVE=(X_MAX-X_MIN)/2;
  const float BACK_PLANE_PERSPECTIVE=1000;
  const float DEFAULT_DISTANCE=2;
  const float ANGLE_STEP=1;

  typedef enum {MODE_DRAW_POINT,MODE_DRAW_LINE,MODE_DRAW_FILL,MODE_DRAW_CHESS} _mode_draw;
  typedef enum {OBJECT_TETRAHEDRON,OBJECT_CUBE, OBJECT_CONE, OBJECT_CYLINDER, OBJECT_SPHERE,OBJECT_PLY, OBJECT_CLAW} _object;
}

class _window;


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _gl_widget : public QOpenGLWidget
{
Q_OBJECT
public:
  _gl_widget(_window *Window1);

  void clear_window();
  void change_projection();
  void change_observer();

  void draw_axis();
  void draw_objects();

protected:
  void resizeGL(int Width1, int Height1) Q_DECL_OVERRIDE;
  void paintGL() Q_DECL_OVERRIDE;
  void initializeGL() Q_DECL_OVERRIDE;
  void keyPressEvent(QKeyEvent *Keyevent) Q_DECL_OVERRIDE;

private slots:
  void tick();

private:
  _window *Window;
  _axis Axis;

  _tetrahedron *Tetrahedron=nullptr;
  _cube *Cube=nullptr;
  _cone *Cone=nullptr;
  _cylinder *Cylinder=nullptr;
  _sphere *Sphere=nullptr;
  _PLY_object3D *Object_ply=nullptr;

  _claw *Claw=nullptr;
  QTimer *Timer;

  _gl_widget_ne::_object Object;

  bool Draw_point;
  bool Draw_line;
  bool Draw_fill;
  bool Draw_chess;

  bool animation;

  float Observer_angle_x;
  float Observer_angle_y;
  float Observer_distance;
};

#endif
