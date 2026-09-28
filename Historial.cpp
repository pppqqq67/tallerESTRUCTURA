#include "Historial.h"
#include <cstdlib>
#include <cstring>

using namespace std;

// CONSTRUCTOR

Historial::Historial() {

    this->registros = nullptr;

    this->cantidad = 0;
}

// DESTRUCTOR

Historial::~Historial() {

    this->limpiar();
}

// AGREGAR REGISTRO

void Historial::agregar(const char* formaUtilizada,bool acerto,bool recibioDanio,int municionRecuperada) {

    RegistroTurno* nuevo;

    nuevo = (RegistroTurno*) realloc(this->registros,(this->cantidad + 1)* sizeof(RegistroTurno));


    if (nuevo == nullptr) {

        return;
    }


    this->registros = nuevo;


    strcpy(this->registros[this->cantidad].formaUtilizada,formaUtilizada);


    this->registros[this->cantidad].acerto =acerto;


    this->registros[this->cantidad].recibioDanio =recibioDanio;


    this->registros[this->cantidad].municionRecuperada =municionRecuperada;


    this->cantidad++;
}

// OBTENER CANTIDAD

int Historial::getCantidad() {

    return this->cantidad;
}

// OBTENER REGISTRO

RegistroTurno Historial::getRegistro(int posicion) {

    RegistroTurno vacio = {};


    if (posicion < 0 ||posicion >= this->cantidad) {

        return vacio;
    }


    return this->registros[posicion];
}

// LIMPIAR

void Historial::limpiar() {

    if (this->registros != nullptr) {

        free(this->registros);

        this->registros = nullptr;
    }


    this->ca
}
