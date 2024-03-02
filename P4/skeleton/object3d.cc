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
    case FLAT: draw_flat(); break;
    case GOURAUD: draw_gouraud(); break;
    case TEXTURE_FLAT: draw_textura_flat(); break;
    case TEXTURE_GOURAUD: draw_textura_gouraud(); break;
    case TEXTURE: draw_textura();
    }
}

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

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

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_flat()
{

    glPolygonMode(GL_FRONT,GL_FILL);

    glEnable(GL_LIGHTING);
    glShadeModel(GL_FLAT);
    glEnable(GL_NORMALIZE);

    glBegin(GL_TRIANGLES);

    for (unsigned int i=0;i<Triangles.size();i++){
        glNormal3fv((GLfloat *) &NormalTriangulos[i]);

        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
    }

    glEnd();

    glDisable(GL_FLAT);
    glDisable(GL_LIGHTING);
    glDisable(GL_NORMALIZE);
}

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_gouraud()
{
    glPolygonMode(GL_FRONT,GL_FILL);

    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    glBegin(GL_TRIANGLES);
    for (unsigned int i=0;i<Triangles.size();i++){
        glNormal3fv((GLfloat *) &NormalVertices[Triangles[i]._0]);
        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);

        glNormal3fv((GLfloat *) &NormalVertices[Triangles[i]._1]);
        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);

        glNormal3fv((GLfloat *) &NormalVertices[Triangles[i]._2]);
        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
    }

    glEnd();

    glDisable(GL_SMOOTH);
    glDisable(GL_LIGHTING);
    glDisable(GL_NORMALIZE);

}

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_textura()
{
    glEnable(GL_TEXTURE_2D);

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glBegin(GL_TRIANGLES);

    int n=0;
    for(unsigned int i = 0; i < Triangles.size(); i++){
        glTexCoord2fv((GLfloat *) &Textura[n]);
        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);

        glTexCoord2fv((GLfloat *) &Textura[n+1]);
        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);

        glTexCoord2fv((GLfloat *) &Textura[n+2]);
        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
        n+=3;
    }

    glEnd();

    glDisable(GL_TEXTURE_2D);
}

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_textura_flat()
{
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glEnable(GL_TEXTURE_2D);

    glShadeModel(GL_FLAT);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);

    glBegin(GL_TRIANGLES);

    int n=0;
    for(unsigned int i = 0; i < Triangles.size(); i++){
        glNormal3fv((GLfloat *) &NormalTriangulos[i]);

        glTexCoord2fv((GLfloat *) &Textura[n]);
        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);

        glTexCoord2fv((GLfloat *) &Textura[n+1]);
        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);

        glTexCoord2fv((GLfloat *) &Textura[n+2]);
        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
        n+=3;
    }

    glEnd();

    glDisable(GL_TEXTURE_2D);

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_NORMALIZE);

}

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_textura_gouraud()
{
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glEnable(GL_TEXTURE_2D);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);

    glBegin(GL_TRIANGLES);

    int n=0;
    for(unsigned int i = 0; i < Triangles.size(); i++){
        glTexCoord2fv((GLfloat *) &Textura[n]);
        glNormal3fv((GLfloat *) &NormalVertices[Triangles[i]._0]);
        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);

        glTexCoord2fv((GLfloat *) &Textura[n+1]);
        glNormal3fv((GLfloat *) &NormalVertices[Triangles[i]._1]);
        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);

        glTexCoord2fv((GLfloat *) &Textura[n+2]);
        glNormal3fv((GLfloat *) &NormalVertices[Triangles[i]._2]);
        glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
        n+=3;
    }

    glEnd();

    glDisable(GL_TEXTURE_2D);

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_NORMALIZE);
}

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::calculoNormal()
{
    for(unsigned int i=0; i<Triangles.size(); ++i){
        // A = P1 - P0
        _vertex3f vectorA = Vertices[Triangles[i]._1] - Vertices[Triangles[i]._0];

        // B = P2 - P0
        _vertex3f vectorB = Vertices[Triangles[i]._2] - Vertices[Triangles[i]._0];

        // N = A * B (cross_product multiplica vectores)
        _vertex3f normal = vectorA.cross_product(vectorB);

        NormalTriangulos.push_back(normal);//y lo añado al vector de triangulos
    }

    //este calculo es más complejo
    //para empezar tengo que tener un vector contador de triangulos en cada vertice
    //con el mismo tamaño que el vector e inicializados con valor 0
    vector <int> n_triangulosVertices(Vertices.size(),0);
    //lo mismo con el vector de normal de vertices
    NormalVertices.resize(Vertices.size(),0);
    for(unsigned int i=0; i<Triangles.size(); ++i){
        //sumo todas las normales de ese triangulo sumatoria(Ni)
        //pag 33 practicas
        NormalVertices[Triangles[i]._0] += NormalTriangulos[i];
        NormalVertices[Triangles[i]._1] += NormalTriangulos[i];
        NormalVertices[Triangles[i]._2] += NormalTriangulos[i];
        //incremento el contador de triangulos de cada vertice, es decir el (n)
        ++n_triangulosVertices[Triangles[i]._0];
        ++n_triangulosVertices[Triangles[i]._1];
        ++n_triangulosVertices[Triangles[i]._2];
    }

    //una vez tenido la suma de todas las normales y el (n)
    //divido la sumatoria de las normales / n (pag 33 practicas)
    for(unsigned int i=0; i<NormalVertices.size(); ++i){
        NormalVertices[i].normalize();
        NormalVertices[i] /=n_triangulosVertices[i];
    }

}
