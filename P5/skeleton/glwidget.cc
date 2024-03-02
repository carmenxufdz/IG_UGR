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


GLfloat POSICION_LUZ_INFINITO[] = {50.0f, 50.0f, 50.0f, 0.0f};
GLfloat POSICION_LUZ[] = {-50.0f, -50.0f, 50.0f, 1.0f};

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
  case Qt::Key_8:Object=OBJECT_TABLERO;break;

  case Qt::Key_A: animation=!animation;
      if(animation) Timer->start();
      else Timer->stop(); break;

  case Qt::Key_P:Draw_point=!Draw_point;break;
  case Qt::Key_L:Draw_line=!Draw_line;break;
  case Qt::Key_F:Draw_fill=!Draw_fill;break;
  // case Qt::Key_O:Draw_selection=!Draw_selection;break;
  //case Qt::Key_C:Draw_chess=!Draw_chess;break;

  case Qt::Key_Left:Observer_angle_y-=ANGLE_STEP;break;
  case Qt::Key_Right:Observer_angle_y+=ANGLE_STEP;break;
  case Qt::Key_Up:Observer_angle_x-=ANGLE_STEP;break;
  case Qt::Key_Down:Observer_angle_x+=ANGLE_STEP;break;
  case Qt::Key_PageUp:
      Observer_distance*=FACTOR_CAMARA;
      break;
  case Qt::Key_PageDown:
      Observer_distance/=FACTOR_CAMARA;
      break;

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
/*
  case Qt::Key_N:Claw->moveBaseX(false); Claw->moveBall(); break;
  case Qt::Key_V:Claw->moveBaseX(true); Claw->moveBall(); break;
  case Qt::Key_B:Claw->moveBaseZ(false); Claw->moveBall(); break;
  case Qt::Key_G:Claw->moveBaseZ(true); Claw->moveBall(); break;
*/
  case Qt::Key_F1: desactivar_todo(); Draw_fill=!Draw_fill; break;
  case Qt::Key_F2: desactivar_todo(); Draw_chess=!Draw_chess; break;
  case Qt::Key_F3: desactivar_todo(); Draw_flat=!Draw_flat; break;
  case Qt::Key_F4: desactivar_todo(); Draw_gouraud=!Draw_gouraud; break;
  case Qt::Key_F5: desactivar_todo(); Draw_textura=!Draw_textura; break;
  case Qt::Key_F6: desactivar_todo(); Draw_textura_flat=!Draw_textura_flat; break;
  case Qt::Key_F7: desactivar_todo(); Draw_textura_gouraud=!Draw_textura_gouraud; break;

  case Qt::Key_J: luz0=!luz0; break;
  case Qt::Key_K: luz1=!luz1; break;
  case Qt::Key_M: tipo=(tipo+1)%5; break;

  case Qt::Key_C: Camera=PERSPECTIVE_PROJECTION; break;
  case Qt::Key_V: Camera=PARALLEL_PROJECTION; break;

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

  float RA = float(Window_height)/float(Window_width);  //Relacion de aspecto, por si el lienzo no fuese cuadrado


  // formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
  // Front_plane>0  Back_plane>PlanoDelantero)

  switch (Camera) {
  case PERSPECTIVE_PROJECTION:
      //glFrustum(X_MIN,X_MAX,Y_MIN,Y_MAX,FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);
      glFrustum(X_MIN,X_MAX,Y_MIN*RA,Y_MAX*RA,FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);
      break;
  case PARALLEL_PROJECTION:
      int mult=Observer_distance*10.0;
      glOrtho(X_MIN*mult,X_MAX*mult,Y_MIN*mult*RA,Y_MAX*mult*RA,FRONT_PLANE_PARALLEL,BACK_PLANE_PARALLEL);
      break;
  }

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
 * Hacer click con el raton
 *
 *
 *
 *****************************************************************************/

void _gl_widget::mousePressEvent(QMouseEvent *Mouseevent){
  if(Mouseevent->buttons() & Qt::RightButton){
      Selection_position_x = Mouseevent->pos().x();
      Selection_position_y = Window_height - Mouseevent->pos().y();//OpenGL asume y=0 abajo de la ventana, la mayoria de SOs asumen y=0 arriba de la ventana.
      Draw_fill = true;
      pick();
      update();
  }
}

/*****************************************************************************//**
 * Evento rueda raton (hacer zoom)
 *
 *
 *
 *****************************************************************************/

void _gl_widget::wheelEvent(QWheelEvent *Wheelevent){
  QPoint puntero = Wheelevent->angleDelta();
  int posicion_y = puntero.ry();

  if(!puntero.isNull()){
        if (posicion_y > 0)         Observer_distance /= FACTOR_CAMARA;
        else if (posicion_y < 0)    Observer_distance *= FACTOR_CAMARA;
  }
  Wheelevent->accept();
  update();
}

/*****************************************************************************//**
 * Evento mover raton (mover camara)
 *
 *
 *
 *****************************************************************************/

void _gl_widget::mouseMoveEvent(QMouseEvent *Mouseevent){
  int nueva_x = Mouseevent->x();   //Cogemos posicion del puntero
  int nueva_y = Mouseevent->y();

  if(Mouseevent->buttons() & Qt::LeftButton){
      //Mover el raton hacia los lados (X) provoca rotacion respecto de eje Y
      if(ultima_x < nueva_x)      Observer_angle_y+=MOUSE_STEP;
      else if(ultima_x > nueva_x) Observer_angle_y-=MOUSE_STEP;

      //Mover raton hacia arriba o abajo (Y) provoca rotacion respecto de eje X
      if(ultima_y < nueva_y)      Observer_angle_x+=MOUSE_STEP;
      else if(ultima_y > nueva_y) Observer_angle_x-=MOUSE_STEP;

      //Actualizamos valores para que no haga cosas raras
      ultima_x = nueva_x;
      ultima_y = nueva_y;
  }
  update();
}
/*****************************************************************************//**
 * Funcion pick
 *
 *
 *
 *****************************************************************************/

void _gl_widget::pick()
{
  makeCurrent();

  // Frame Buffer Object to do the off-screen rendering
  GLuint FBO;
  glGenFramebuffers(1,&FBO);
  glBindFramebuffer(GL_FRAMEBUFFER,FBO);

  // Texture for drawing
  GLuint Color_texture;
  glGenTextures(1,&Color_texture);
  glBindTexture(GL_TEXTURE_2D,Color_texture);
  // RGBA8
  glTexStorage2D(GL_TEXTURE_2D,1,GL_RGBA8, Window_width,Window_height);
  // this implies that there is not mip mapping
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

  // Texure for computing the depth
  GLuint Depth_texture;
  glGenTextures(1,&Depth_texture);
  glBindTexture(GL_TEXTURE_2D,Depth_texture);
  // Float
  glTexStorage2D(GL_TEXTURE_2D,1,GL_DEPTH_COMPONENT24, Window_width,Window_height);

  // Attatchment of the textures to the FBO
  glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,Color_texture,0);
  glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,Depth_texture,0);

  // OpenGL will draw to these buffers (only one in this case)
  static const GLenum Draw_buffers[]={GL_COLOR_ATTACHMENT0};
  glDrawBuffers(1,Draw_buffers);

  /*************************/

  // dibujar escena para seleccion

  /*************************/
  clear_window();//borra la ventana
  change_projection();//have los cambios de projección
  change_observer();//hace cambios de observador

  //dibuja el escenario
  switch (Object){
      case OBJECT_TETRAHEDRON:Tetrahedron->draw(SELECTION);break;
      case OBJECT_CUBE:Cube->draw(SELECTION);break;
      case OBJECT_CONE:Cone->draw(SELECTION);break;
      case OBJECT_CYLINDER:Cylinder->draw(SELECTION);break;
      case OBJECT_SPHERE:Sphere->draw(SELECTION); break;
      case OBJECT_PLY:Object_ply->draw(SELECTION); break;
      case OBJECT_CLAW:Claw->draw(SELECTION); break;
      case OBJECT_TABLERO:Tablero->draw(SELECTION);break;
      default:break;
  }

  // get the pixel
  int Color;
  glReadBuffer(GL_FRONT);
  glPixelStorei(GL_PACK_ALIGNMENT,1);
  glReadPixels(Selection_position_x,Selection_position_y,1,1,GL_RGBA,GL_UNSIGNED_BYTE,&Color);

  /*************************/

  // convertir de RGB a identificador
  uint R = uint((Color & 0x000000FF));
  uint G = uint((Color & 0x0000FF00) >> 8);
  uint B = uint((Color & 0x00FF0000) >> 16);

  // actualizar el identificador de la parte seleccionada en el objeto
  int Triangulo_pick = (R << 16) + (G << 8) + B;
  // Tenemos 2^24 = 16777216 colores, pero el último es el blanco, que debemos descartar (representa no seleccion/vacio)
  if(Triangulo_pick == 16777215) Triangulo_pick = -1;

  /*************************/

  //dibuja el triangulo seleccionado
  switch(Object){
    case OBJECT_TETRAHEDRON: Tetrahedron->actualizar_triangulo_pick(Triangulo_pick); break;
    case OBJECT_CUBE: Cube->actualizar_triangulo_pick(Triangulo_pick); break;
    case OBJECT_CONE: Cone->actualizar_triangulo_pick(Triangulo_pick); break;
    case OBJECT_CYLINDER: Cylinder->actualizar_triangulo_pick(Triangulo_pick); break;
    case OBJECT_SPHERE: Sphere->actualizar_triangulo_pick(Triangulo_pick); break;
    case OBJECT_PLY: Object_ply->actualizar_triangulo_pick(Triangulo_pick); break;
    case OBJECT_CLAW: Claw->actualizar_triangulo_pick(Triangulo_pick); break;
    case OBJECT_TABLERO: Tablero->actualizar_triangulo_pick(Triangulo_pick); break;
    default: break;
  }

  glDeleteTextures(1,&Color_texture);
  glDeleteTextures(1,&Depth_texture);
  glDeleteFramebuffers(1,&FBO);
  // the normal framebuffer takes the control of drawing
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER,defaultFramebufferObject());

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

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *)&AMBIENTE);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *)&DIFUSA);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *)&ESPECULAR);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, BRILLO);

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
    case OBJECT_TABLERO:Tablero->draw(PUNTO);break;
    default:break;
    }
  }

  if (Draw_line){
    glLineWidth(3);
    glColor3fv((GLfloat *) &RED);
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron->draw(LINE);break;
    case OBJECT_CUBE:Cube->draw(LINE);break;
    case OBJECT_CONE:Cone->draw(LINE);break;
    case OBJECT_CYLINDER:Cylinder->draw(LINE);break;
    case OBJECT_SPHERE:Sphere->draw(LINE);break;
    case OBJECT_PLY:Object_ply->draw(LINE);break;
    case OBJECT_CLAW:Claw->draw(LINE); break;
    case OBJECT_TABLERO:Tablero->draw(LINE);break;
    default:break;
    }
  }

  if (Draw_fill){
    glColor3fv((GLfloat *) &BLUE);
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron->draw(FILL);break;
    case OBJECT_CUBE:Cube->draw(FILL);break;
    case OBJECT_CONE:Cone->draw(FILL);break;
    case OBJECT_CYLINDER:Cylinder->draw(FILL);break;
    case OBJECT_SPHERE:Sphere->draw(FILL);break;
    case OBJECT_PLY:Object_ply->draw(FILL);break;
    case OBJECT_CLAW:Claw->draw(FILL); break;
    case OBJECT_TABLERO:Tablero->draw(FILL);break;
    default:break;
    }
  }

  if (Draw_selection){
      switch (Object){
      case OBJECT_TETRAHEDRON:Tetrahedron->draw(SELECTION);break;
      case OBJECT_CUBE:Cube->draw(SELECTION);break;
      case OBJECT_CONE:Cone->draw(SELECTION);break;
      case OBJECT_CYLINDER:Cylinder->draw(SELECTION);break;
      case OBJECT_SPHERE:Sphere->draw(SELECTION); break;
      case OBJECT_PLY:Object_ply->draw(SELECTION); break;
      case OBJECT_CLAW:Claw->draw(SELECTION); break;
      case OBJECT_TABLERO:Tablero->draw(SELECTION);break;
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
    case OBJECT_TABLERO:Tablero->draw(CHESS);break;
    default:break;
    }
  }

  if (Draw_flat){
    //para la animación de la luz magenta
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotated(tiempo,0,1,0);
    luz_magenta();
    glPopMatrix();

    luz_infinito();

    //ACTIVA/DESACTIVA LUZ 1
    if(luz0)
        glEnable(GL_LIGHT0);
    else
        glDisable(GL_LIGHT0);

    //ACTIVA/DESACTIVA LUZ 2
    if(luz1)
        glEnable(GL_LIGHT1);
    else
        glDisable(GL_LIGHT1);

    changeMaterial();

    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron->draw(FLAT);break;
    case OBJECT_CUBE:Cube->draw(FLAT);break;
    case OBJECT_CONE:Cone->draw(FLAT);break;
    case OBJECT_CYLINDER:Cylinder->draw(FLAT);break;
    case OBJECT_SPHERE:Sphere->draw(FLAT);break;
    case OBJECT_PLY:Object_ply->draw(FLAT);break;
    case OBJECT_CLAW:Claw->draw(FLAT); break;
    case OBJECT_TABLERO:Tablero->draw(FLAT);break;
    default:break;
    }
  }

  if (Draw_gouraud){
    //para la animación de la luz magenta
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotated(tiempo,0,1,0);
    luz_magenta();
    glPopMatrix();

    luz_infinito();

    //ACTIVA/DESACTIVA LUZ 1
    if(luz0)
        glEnable(GL_LIGHT0);
    else
        glDisable(GL_LIGHT0);

    //ACTIVA/DESACTIVA LUZ 2
    if(luz1)
        glEnable(GL_LIGHT1);
    else
        glDisable(GL_LIGHT1);

    changeMaterial();

    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron->draw(GOURAUD);break;
    case OBJECT_CUBE:Cube->draw(GOURAUD);break;
    case OBJECT_CONE:Cone->draw(GOURAUD);break;
    case OBJECT_CYLINDER:Cylinder->draw(GOURAUD);break;
    case OBJECT_SPHERE:Sphere->draw(GOURAUD);break;
    case OBJECT_PLY:Object_ply->draw(GOURAUD);break;
    case OBJECT_CLAW:Claw->draw(GOURAUD); break;
    case OBJECT_TABLERO:Tablero->draw(GOURAUD);break;
    default:break;
    }
  }

  if (Draw_textura){

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glColor3fv((GLfloat *) &WHITE);

    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron->draw(TEXTURE);break;
    case OBJECT_CUBE:Cube->draw(TEXTURE);break;
    case OBJECT_CONE:Cone->draw(TEXTURE);break;
    case OBJECT_CYLINDER:Cylinder->draw(TEXTURE);break;
    case OBJECT_SPHERE:Sphere->draw(TEXTURE);break;
    case OBJECT_PLY:Object_ply->draw(TEXTURE);break;
    case OBJECT_CLAW:Claw->draw(TEXTURE); break;
    case OBJECT_TABLERO:Tablero->draw(TEXTURE);break;
    default:break;
    }
  }
  if (Draw_textura_flat){

    //Asegurar que se utilice color de textura y no el del relleno
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3fv((GLfloat *) &WHITE);

    //para la animación de la luz magenta
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotated(tiempo,0,1,0);
    luz_magenta();
    glPopMatrix();

    luz_infinito();

    //ACTIVA/DESACTIVA LUZ 1
    if(luz0)
        glEnable(GL_LIGHT0);
    else
        glDisable(GL_LIGHT0);

    //ACTIVA/DESACTIVA LUZ 2
    if(luz1)
        glEnable(GL_LIGHT1);
    else
        glDisable(GL_LIGHT1);



    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron->draw(TEXTURE_FLAT);break;
    case OBJECT_CUBE:Cube->draw(TEXTURE_FLAT);break;
    case OBJECT_CONE:Cone->draw(TEXTURE_FLAT);break;
    case OBJECT_CYLINDER:Cylinder->draw(TEXTURE_FLAT);break;
    case OBJECT_SPHERE:Sphere->draw(TEXTURE_FLAT);break;
    case OBJECT_PLY:Object_ply->draw(TEXTURE_FLAT);break;
    case OBJECT_CLAW:Claw->draw(TEXTURE_FLAT); break;
    case OBJECT_TABLERO:Tablero->draw(TEXTURE_FLAT);break;
    default:break;
    }
  }
  if (Draw_textura_gouraud){

    //para la animación de la luz magenta
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotated(tiempo,0,1,0);
    luz_magenta();
    glPopMatrix();

    luz_infinito();

    //ACTIVA/DESACTIVA LUZ 1
    if(luz0)
        glEnable(GL_LIGHT0);
    else
        glDisable(GL_LIGHT0);

    //ACTIVA/DESACTIVA LUZ 2
    if(luz1)
        glEnable(GL_LIGHT1);
    else
        glDisable(GL_LIGHT1);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3fv((GLfloat *) &WHITE);

    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron->draw(TEXTURE_GOURAUD);break;
    case OBJECT_CUBE:Cube->draw(TEXTURE_GOURAUD);break;
    case OBJECT_CONE:Cone->draw(TEXTURE_GOURAUD);break;
    case OBJECT_CYLINDER:Cylinder->draw(TEXTURE_GOURAUD);break;
    case OBJECT_SPHERE:Sphere->draw(TEXTURE_GOURAUD);break;
    case OBJECT_PLY:Object_ply->draw(TEXTURE_GOURAUD);break;
    case OBJECT_CLAW:Claw->draw(TEXTURE_GOURAUD); break;
    case OBJECT_TABLERO:Tablero->draw(TEXTURE_GOURAUD);break;
    default:break;
    }
  }
}

/*****************************************************************************//**
 * Calculo Normal
 *
 *
 *
 *****************************************************************************/

void _gl_widget::calculoNormal()
{
  Tetrahedron->calculoNormal();
  Cube->calculoNormal();
  Cone->calculoNormal();
  Cylinder->calculoNormal();
  Sphere->calculoNormal();
  Object_ply->calculoNormal();
  Claw->calculoNormal();
  Tablero->calculoNormal();
}

/*****************************************************************************//**
 * Luz Blanca Situada en el Infinito
 *
 *
 *
 *****************************************************************************/

void _gl_widget::luz_infinito()
{

  glLightfv(GL_LIGHT0,GL_POSITION,POSICION_LUZ_INFINITO);
}

/*****************************************************************************//**
 * Luz Magenta
 *
 *
 *
 *****************************************************************************/

void _gl_widget::luz_magenta()
{
    glLightfv(GL_LIGHT1,GL_POSITION,POSICION_LUZ);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,LUZ_MAGENTA);
    glLightfv(GL_LIGHT1,GL_SPECULAR,LUZ_MAGENTA);
}

/*****************************************************************************//**
 * Cambiar Material
 *
 *
 *
 *****************************************************************************/

void _gl_widget::changeMaterial()
{
  switch(tipo)
  {
  case 0:
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *)&AMBIENTE_RUBI);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *)&DIFUSA_RUBI);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *)&ESPECULAR_RUBI);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, BRILLO_RUBI);
        break;
  case 1:
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *)&AMBIENTE_TURQUESA);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *)&DIFUSA_TURQUESA);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *)&ESPECULAR_TURQUESA);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, BRILLO_TURQUESA);
        break;
  case 2:
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *)&AMBIENTE_OBSIDIANA);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *)&DIFUSA_OBSIDIANA);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *)&ESPECULAR_OBSIDIANA);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, BRILLO_OBSIDIANA);
        break;
  case 3:
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *)&AMBIENTE_ESMERALDA);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *)&DIFUSA_ESMERALDA);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *)&ESPECULAR_ESMERALDA);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, BRILLO_ESMERALDA);
        break;
  case 4:
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *)&AMBIENTE_PERLADO);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *)&DIFUSA_PERLADO);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *)&ESPECULAR_PERLADO);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, BRILLO_PERLADO);
        break;
  }
}

void _gl_widget::load_file(QString &fileName,QImage &Image)
{
    QImageReader Reader(fileName);
    Reader.setAutoTransform(true);
    Image = Reader.read();
    if (Image.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                               tr("Cannot load %1.").arg(QDir::toNativeSeparators(fileName)));
        exit(-1);
    }
    Image=Image.mirrored();
    Image=Image.convertToFormat(QImage::Format_RGB888);

    // Code to control the application of the texture
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Code to pass the image to OpenGL to form a texture
    glTexImage2D(GL_TEXTURE_2D,0,3,Image.width(),Image.height(),0,GL_RGB,GL_UNSIGNED_BYTE,Image.bits());


}

/*****************************************************************************//**
 * Evento asociado al timer
 *
 *
 *
 *****************************************************************************/

void _gl_widget::tick()
{
  tiempo+=1;
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


    glewExperimental = GL_TRUE;
    int err = glewInit();
    if (GLEW_OK != err){
        // Problem: glewInit failed, something is seriously wrong.
        QMessageBox MsgBox(this);
        MsgBox.setText("Error: There is not OpenGL drivers\n\nPlease,\
        look for the information of your GPU\
        (AMD, INTEL or NVIDIA) and install the drivers");
        MsgBox.exec();
        Window->close();
    }

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

  Window_width=width();
  Window_height=height();

  Draw_point=false;
  Draw_line=true;
  Draw_fill=false;
  Draw_chess=false;
  Draw_flat=false;
  Draw_selection=false;
  Draw_gouraud=false;
  Draw_textura=false;
  Draw_textura_flat=false;
  Draw_textura_gouraud=false;

  luz0 = false;
  luz1 = false;

  Camera=PERSPECTIVE_PROJECTION;

  tiempo = 0;
  tipo = 0;

  Tetrahedron=new _tetrahedron();
  Cube=new _cube();
  Cone=new _cone();
  Cylinder=new _cylinder();
  Sphere=new _sphere();
  Object_ply=new _PLY_object3D("../skeleton/ply_models/beethoven.ply");
  Tablero=new _chess_board();

  Claw=new _claw();

  animation=false;
  Timer = new QTimer();
  Timer->setInterval(20);
  connect(Timer, SIGNAL(timeout()), this, SLOT(tick()));

  fileName = new QString("../skeleton/texturas/dia_8192.jpg");
  Image = new QImage();

  calculoNormal();

  load_file(*fileName, *Image);

  ultima_x = ultima_y = 0;


}
