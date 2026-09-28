#ifndef FORMA_H
#define FORMA_H

#include <string>
#include "Coordenada.h"

using namespace std;

class Forma {

private:

    string nombre;

    int municion;

    Coordenada* coordenadas;

    int cantidadImpactos;


public:

    Forma();

    Forma(string nombre,int municion);

    ~Forma();


    string getNombre();

    int getMunicion();

    void setNombre(string nombre);

    void setMunicion(int municion);


    void restarMunicion();

    void agregarMunicion();


    void agregarCoordenada(int fila,int columna);


    Coordenada getCoordenada(int posicion);


    int getCantidadImpactos();
};

#endif