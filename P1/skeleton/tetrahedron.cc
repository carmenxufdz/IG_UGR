/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2023
 * GPL 3
 */


#include "tetrahedron.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_tetrahedron::_tetrahedron(float Size)
{
  Vertices.resize(4);

  Vertices[0]=_vertex3f(-Size/2,-Size/2,-Size/2);
  Vertices[1]=_vertex3f(0,-Size/2,Size/2);
  Vertices[2]=_vertex3f(Size/2,-Size/2,-Size/2);
  Vertices[3]=_vertex3f(0,Size/2,0);

  Edges.resize(6);
  Edges[0]=_vertex2ui(0,1);
  Edges[1]=_vertex2ui(0,2);
  Edges[2]=_vertex2ui(0,3);
  Edges[3]=_vertex2ui(1,2);
  Edges[4]=_vertex2ui(1,3);
  Edges[5]=_vertex2ui(2,3);

  Triangles.resize(4);

  Triangles[0]=_vertex3ui(0,1,3);
  Triangles[1]=_vertex3ui(1,2,3);
  Triangles[2]=_vertex3ui(2,0,3);
  Triangles[3]=_vertex3ui(0,2,1);
}

