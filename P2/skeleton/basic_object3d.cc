/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2023
 * GPL 3
 */


#include "basic_object3d.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _basic_object3D::draw_point()
{
  glBegin(GL_POINTS);
  for (unsigned int i=0;i<Vertices.size();i++){
    glVertex3fv((GLfloat *) &Vertices[i]);
  }
  glEnd();
}

void _wire_object3D::draw_lines()
{
  glBegin(GL_LINES);
  for (unsigned int i=0; i<Edges.size(); i++){
    glVertex3fv((GLfloat *) &Vertices[Edges[i]._0]);
    glVertex3fv((GLfloat *) &Vertices[Edges[i]._1]);
  }
  glEnd();
}
