/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2023
 * GPL 3
 */


#include "object3d.h"

using namespace _colors_ne;


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/
void _object3D::draw(_mode_draw mode)
{
    switch(mode)
    {
    case PUNTO: draw_point(); break;
    case LINE: draw_line(); break;
    case FILL: draw_fill(); break;
    case CHESS: draw_chess(); break;
    }
}

void _object3D::draw_line()
{
    // draw_lines();

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    glBegin(GL_TRIANGLES);
    for(unsigned int i=0; i<Triangles.size(); i++)
    {
        glVertex3fv((GLfloat *)&Vertices[Triangles[i]._0]);
        glVertex3fv((GLfloat *)&Vertices[Triangles[i]._1]);
        glVertex3fv((GLfloat *)&Vertices[Triangles[i]._2]);
    }
    glEnd();

}


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_fill()
{
    glPolygonMode(GL_FRONT,GL_FILL);

    glBegin(GL_TRIANGLES);
    for(unsigned int i=0; i<Triangles.size(); i++)
    {
        glVertex3fv((GLfloat *)&Vertices[Triangles[i]._0]);
        glVertex3fv((GLfloat *)&Vertices[Triangles[i]._1]);
        glVertex3fv((GLfloat *)&Vertices[Triangles[i]._2]);
    }
    glEnd();
}


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_chess()
{
    glPolygonMode(GL_FRONT,GL_FILL);

    glBegin(GL_TRIANGLES);
    for(unsigned int i=0; i<Triangles.size(); i++)
    {
        glColor3fv((GLfloat *)&CYAN);

        if(i%2==0) glColor3fv((GLfloat *)&YEllOW);

        glVertex3fv((GLfloat *)&Vertices[Triangles[i]._0]);
        glVertex3fv((GLfloat *)&Vertices[Triangles[i]._1]);
        glVertex3fv((GLfloat *)&Vertices[Triangles[i]._2]);
    }
    glEnd();
}
