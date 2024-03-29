#include "ply.h"

_PLY_object3D::_PLY_object3D(string file_name)
{
    _file_ply archivo;

    if(archivo.open(file_name))
    {
        archivo.read(coordinates, positions);
        archivo.close();

        Vertices.resize(coordinates.size()/3);
        int tam = Vertices.size();
        for(int i=0; i<tam; i++)
        {
            Vertices[i]=_vertex3f(coordinates[i*3], coordinates[(i*3)+1], coordinates[(i*3)+2]);
        }

        Triangles.resize(positions.size()/3);
        tam = Triangles.size();
        for(int i=0; i<tam; i++)
        {
            Triangles[i]=_vertex3ui(positions[i*3], positions[(i*3)+1], positions[(i*3)+2]);
        }
    }
    else
    {
        cout << "Error: Archivo no leído" << endl;
    }

}

_PLY_object3D::_PLY_object3D(string file_name, int num)
{
    _file_ply archivo;

    if(archivo.open(file_name))
    {
        archivo.read(coordinates, positions);
        archivo.close();

        Vertices.resize(coordinates.size()/3);
        int tam = Vertices.size();
        for(int i=0; i<tam; i++)
        {
            Vertices[i]=_vertex3f(coordinates[i*3], coordinates[(i*3)+1], coordinates[(i*3)+2]);
        }

        Triangles.resize(positions.size()/3);
        tam = Triangles.size();
        for(int i=0; i<tam; i++)
        {
            Triangles[i]=_vertex3ui(positions[i*3], positions[(i*3)+1], positions[(i*3)+2]);
        }
    }
    else
    {
        cout << "Error: Archivo no leído" << endl;
    }

    turns(num);
}
