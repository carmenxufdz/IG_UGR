/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2023
 * GPL 3
 */


#include "glwidget.h"
#include "window.h"

using namespace std;
using namespace _gl_widget_ne;
using namespace _colors_ne;


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_gl_widget::_gl_widget(_window *Window1):Window(Window1)
{
  setMinimumSize(300, 300);
  setFocusPolicy(Qt::StrongFocus);
}


/*****************************************************************************//**
 * Evento tecla pulsada
 *
 *
 *
 *****************************************************************************/

void _gl_widget::keyPressEvent(QKeyEvent *Keyevent)
{
  switch(Keyevent->key()){
  case Qt::Key_1:Object=OBJECT_TETRAHEDRON;break;
  case Qt::Key_2:Object=OBJECT_CUBE;break;
  case Qt::Key_3:Object=OBJECT_CONE;break;
  case Qt::Key_4:Object=OBJECT_CYLINDER;break;
  case Qt::Key_5:Object=OBJECT_SPHERE;break;
  case Qt::Key_6:Object=OBJECT_PLY;break;
  case Qt::Key_7:Object=OBJECT_CLAW;break;

  case Qt::Key_P:Draw_point=!Draw_point;break;
  case Qt::Key_L:Draw_line=!Draw_line;break;
  case Qt::Key_F:Draw_fill=!Draw_fill;break;
  case Qt::Key_C:Draw_chess=!Draw_chess;break;

  case Qt::Key_Left:Observer_angle_y-=ANGLE_STEP;break;
  case Qt::Key_Right:Observer_angle_y+=ANGLE_STEP;break;
  case Qt::Key_Up:Observer_angle_x-=ANGLE_STEP;break;
  case Qt::Key_Down:Observer_angle_x+=ANGLE_STEP;break;
  case Qt::Key_PageUp:Observer_distance*=1.2;break;
  case Qt::Key_PageDown:Observer_distance/=1.2;break;

  case Qt::Key_Q:Claw->moveClaw(false); Claw->moveBall(); break;
  case Qt::Key_W:Claw->moveClaw(true); Claw->moveBall(); break;
  case Qt::Key_S:Claw->moveArm(true); Claw->moveBall(); break;
  case Qt::Key_D:Claw->moveArm(false); Claw->moveBall(); break;
  case Qt::Key_Z:Claw->RotateArm(false); Claw->moveBall(); break;
  case Qt::Key_X:Claw->RotateArm(true); Claw->moveBall(); break;

  case Qt::Key_E:Claw->modMoveClaw(false); break;
  case Qt::Key_R:Claw->modMoveClaw(true); break;
  case Qt::Key_T:Claw->modMove(false); break;
  case Qt::Key_Y:Claw->modMove(true); break;
  case Qt::Key_U:Claw->modRot(false); break;
  case Qt::Key_I:Claw->modRot(true); break;


  case Qt::Key_M:Claw->moveBaseX(false); Claw->moveBall(); break;
  case Qt::Key_B:Claw->moveBaseX(true); Claw->moveBall(); break;
  case Qt::Key_N:Claw->moveBaseZ(false); Claw->moveBall(); break;
  case Qt::Key_H:Claw->moveBaseZ(true); Claw->moveBall(); break;

  case Qt::Key_A: animation=!animation; if(animation) Timer->start(); else Timer->stop(); break;

  }

  update();
}


/*****************************************************************************//**
 * Limpiar ventana
 *
 *
 *
 *****************************************************************************/

void _gl_widget::clear_window()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}



/*****************************************************************************//**
 * Funcion para definir la transformación de proyeccion
 *
 *
 *
 *****************************************************************************/

void _gl_widget::change_projection()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
  // Front_plane>0  Back_plane>PlanoDelantero)
  glFrustum(X_MIN,X_MAX,Y_MIN,Y_MAX,FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);
}



/*****************************************************************************//**
 * Funcion para definir la transformación de vista (posicionar la camara)
 *
 *
 *
 *****************************************************************************/

void _gl_widget::change_observer()
{
  // posicion del observador
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0,0,-Observer_distance);
  glRotatef(Observer_angle_x,1,0,0);
  glRotatef(Observer_angle_y,0,1,0);
}


/*****************************************************************************//**
 * Funcion que dibuja los objetos
 *
 *
 *
 *****************************************************************************/

void _gl_widget::draw_objects()
{
  Axis.draw_line();

  if (Draw_point){
    glPointSize(5);
    glColor3fv((GLfloat *) &RED);
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron->draw(PUNTO);break;
    case OBJECT_CUBE:Cube->draw(PUNTO);break;
    case OBJECT_CONE:Cone->draw(PUNTO);break;
    case OBJECT_CYLINDER:Cylinder->draw(PUNTO);break;
    case OBJECT_SPHERE:Sphere->draw(PUNTO);break;
    case OBJECT_PLY:Object_ply->draw(PUNTO);break;
    case OBJECT_CLAW:Claw->draw(PUNTO); break;
    default:break;
    }
  }

  if (Draw_line){
    glLineWidth(3);
    glColor3fv((GLfloat *) &BLACK);
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron->draw(LINE);break;
    case OBJECT_CUBE:Cube->draw(LINE);break;
    case OBJECT_CONE:Cone->draw(LINE);break;
    case OBJECT_CYLINDER:Cylinder->draw(LINE);break;
    case OBJECT_SPHERE:Sphere->draw(LINE);break;
    case OBJECT_PLY:Object_ply->draw(LINE);break;
    case OBJECT_CLAW:Claw->draw(LINE); break;
    default:break;
    }
  }

  if (Draw_fill){
    glColor3fv((GLfloat *) &RED);
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron->draw(FILL);break;
    case OBJECT_CUBE:Cube->draw(FILL);break;
    case OBJECT_CONE:Cone->draw(FILL);break;
    case OBJECT_CYLINDER:Cylinder->draw(FILL);break;
    case OBJECT_SPHERE:Sphere->draw(FILL);break;
    case OBJECT_PLY:Object_ply->draw(FILL);break;
    case OBJECT_CLAW:Claw->draw(FILL); break;
    default:break;
    }
  }

  if (Draw_chess){
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron->draw(CHESS);break;
    case OBJECT_CUBE:Cube->draw(CHESS);break;
    case OBJECT_CONE:Cone->draw(CHESS);break;
    case OBJECT_CYLINDER:Cylinder->draw(CHESS);break;
    case OBJECT_SPHERE:Sphere->draw(CHESS);break;
    case OBJECT_PLY:Object_ply->draw(CHESS);break;
    case OBJECT_CLAW:Claw->draw(CHESS); break;
    default:break;
    }
  }
}

/*****************************************************************************//**
 * Evento asociado al timer
 *
 *
 *
 *****************************************************************************/

void _gl_widget::tick()
{
  Claw->update();
  Claw->moveBall();
  update();
}


/*****************************************************************************//**
 * Evento de dibujado
 *
 *
 *
 *****************************************************************************/

void _gl_widget::paintGL()
{
  clear_window();
  change_projection();
  change_observer();
  draw_objects();
}


/*****************************************************************************//**
 * Evento de cambio de tamaño de la ventana
 *
 *
 *
 *****************************************************************************/

void _gl_widget::resizeGL(int Width1, int Height1)
{
  glViewport(0,0,Width1,Height1);
}


/*****************************************************************************//**
 * Inicialización de OpenGL
 *
 *
 *
 *****************************************************************************/

void _gl_widget::initializeGL()
{
  const GLubyte* strm;

  strm = glGetString(GL_VENDOR);
  std::cerr << "Vendor: " << strm << "\n";
  strm = glGetString(GL_RENDERER);
  std::cerr << "Renderer: " << strm << "\n";
  strm = glGetString(GL_VERSION);
  std::cerr << "OpenGL Version: " << strm << "\n";

  if (strm[0] == '1'){
    std::cerr << "Only OpenGL 1.X supported!\n";
    exit(-1);
  }

  strm = glGetString(GL_SHADING_LANGUAGE_VERSION);
  std::cerr << "GLSL Version: " << strm << "\n";

  int Max_texture_size=0;
  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &Max_texture_size);
  std::cerr << "Max texture size: " << Max_texture_size << "\n";

  glClearColor(1.0,1.0,1.0,1.0);
  glEnable(GL_DEPTH_TEST);;

  Observer_angle_x=0;
  Observer_angle_y=0;
  Observer_distance=DEFAULT_DISTANCE;

  Draw_point=false;
  Draw_line=true;
  Draw_fill=false;
  Draw_chess=false;

  Tetrahedron=new _tetrahedron();
  Cube=new _cube();
  Cone=new _cone();
  Cylinder=new _cylinder();
  Sphere=new _sphere();
  Object_ply=new _PLY_object3D("../skeleton/ply_models/sandal.ply");

  Claw=new _claw();

  animation=false;
  Timer = new QTimer();
  Timer->setInterval(20);
  connect(Timer, SIGNAL(timeout()), this, SLOT(tick()));


}
