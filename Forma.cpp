#include "Forma.h"

// CONSTRUCTOR

Forma::Forma() {

    this->nombre = "";

    this->municion = 0;

    this->coordenadas = nullptr;

    this->cantidadImpactos = 0;
}

// CONSTRUCTOR PARAMETRO

Forma::Forma(string nombre,int municion) {

    this->nombre = nombre;

    this->municion = municion;

    this->coordenadas = nullptr;

    this->cantidadImpactos = 0;
}

// DESTRUCTOR

Forma::~Forma() {

    delete[] this->coordenadas;

    this->coordenadas = nullptr;

    this->cantidadImpactos = 0;
}

// GET NOMBRE

string Forma::getNombre() {

    return this->nombre;
}

// GET MUNICION

int Forma::getMunicion() {

    return this->municion;
}

// SET NOMBRE

void Forma::setNombre(string nombre) {

    this->nombre = nombre;
}

// SET MUNICION

void Forma::setMunicion(int municion) {

    this->municion = municion;
}

// RESTAR MUNICION

void Forma::restarMunicion() {

    if (this->municion > 0) {

        this->municion--;
    }
}

// AGREGAR MUNICION


void Forma::agregarMunicion() {

    this->municion++;
}

// AGREGAR COORDENADA

void Forma::agregarCoordenada(int fila,int columna) {

    Coordenada* nuevo =new Coordenada[this->cantidadImpactos + 1];


    for (int i = 0;i < this->cantidadImpactos;i++) {

        nuevo[i] =this->coordenadas[i];

    }


    nuevo[this->cantidadImpactos] =Coordenada(fila,columna);


    delete[] this->coordenadas;


    this->coordenadas = nuevo;

    this->cantidadImpactos++;
}

// GET COORDENADA

Coordenada Forma::getCoordenada(int posicion) {

    if (posicion < 0 ||posicion >= this->cantidadImpactos) {
        return Coordenada();
    }

    return this->coordenadas[posicion];
}

// GET CANTIDAD IMPACTOS

int Forma::getCantidadImpactos() {

    return this->cantidadImpactos;
}
