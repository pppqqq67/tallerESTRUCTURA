#include "Matriz.h"
#include <iostream>

using namespace std;

// CONSTRUCTOR

Matriz::Matriz(int filas, int columnas) {

    this->filas = filas;
    this->columnas = columnas;


    this->cabecerasFila =new Nodo*[this->filas];

    this->cabecerasColumna =new Nodo*[this->columnas];


    // CREAR CABECERAS DE FILAS

    for (int i = 0; i < this->filas; i++) {

        this->cabecerasFila[i] =new Nodo(i, -1, "");

        this->cabecerasFila[i]->siguienteFila =this->cabecerasFila[i];
    }


    // CREAR CABECERAS DE COLUMNAS

    for (int i = 0; i < this->columnas; i++) {

        this->cabecerasColumna[i] =new Nodo(-1, i, "");

        this->cabecerasColumna[i]->siguienteColumna =this->cabecerasColumna[i];
    }
}


// DESTRUCTOR

Matriz::~Matriz() {

    this->liberar();
}


// POSICION VALIDA

bool Matriz::posicionValida(int fila,int columna) const {

    return fila >= 0 &&fila < this->filas &&columna >= 0 &&columna < this->columnas;
}


// INSERTAR

void Matriz::insertar(int fila,int columna,string tipo) {

    if (!this->posicionValida(fila, columna)) {

        return;

    }


    // VERIFICAR SI YA EXISTE

    Nodo* existente =this->buscar(fila, columna);


    if (existente != nullptr) {

        existente->tipo = tipo;

        return;
    }


    // CABECERA DE LA FILA

    Nodo* cabeceraFila =this->cabecerasFila[fila];


    Nodo* anteriorFila =cabeceraFila;


    Nodo* actualFila =cabeceraFila->siguienteFila;


    // BUSCAR POSICION EN LA FILA

    while (actualFila != cabeceraFila &&actualFila->columna < columna) {

        anteriorFila = actualFila;

        actualFila =actualFila->siguienteFila;
    }


    // CABECERA DE LA COLUMNA

    Nodo* cabeceraColumna =this->cabecerasColumna[columna];


    Nodo* anteriorColumna =cabeceraColumna;


    Nodo* actualColumna =cabeceraColumna->siguienteColumna;


    // BUSCAR POSICION EN LA COLUMNA

    while (actualColumna != cabeceraColumna &&actualColumna->fila < fila) {

        anteriorColumna = actualColumna;

        actualColumna =actualColumna->siguienteColumna;
    }


    // CREAR NODO

    Nodo* nuevo =new Nodo(fila, columna, tipo);


    // ENLAZAR EN FILA

    nuevo->siguienteFila =actualFila;

    anteriorFila->siguienteFila =nuevo;


    // ENLAZAR EN COLUMNA

    nuevo->siguienteColumna =actualColumna;

    anteriorColumna->siguienteColumna =nuevo;
}


// BUSCAR

Matriz::Nodo* Matriz::buscar(int fila,int columna) {

    if (!this->posicionValida(fila, columna)) {

        return nullptr;
    }


    Nodo* cabecera =this->cabecerasFila[fila];


    Nodo* actual =cabecera->siguienteFila;


    while (actual != cabecera) {

        if (actual->columna == columna) {

            return actual;
        }


        if (actual->columna > columna) {

            return nullptr;
        }


        actual =actual->siguienteFila;
    }


    return nullptr;
}


// ELIMINAR

void Matriz::eliminar(int fila,int columna) {

    Nodo* objetivo =this->buscar(fila, columna);


    if (objetivo == nullptr) {

        return;
    }


    // ELIMINAR DE LA FILA

    Nodo* cabeceraFila =this->cabecerasFila[fila];


    Nodo* anteriorFila =cabeceraFila;


    Nodo* actualFila =cabeceraFila->siguienteFila;


    while (actualFila != cabeceraFila &&actualFila != objetivo) {

        anteriorFila = actualFila;

        actualFila =actualFila->siguienteFila;
    }


    if (actualFila == objetivo) {

        anteriorFila->siguienteFila =objetivo->siguienteFila;

    }


    // ELIMINAR DE LA COLUMNA

    Nodo* cabeceraColumna =this->cabecerasColumna[columna];


    Nodo* anteriorColumna =cabeceraColumna;


    Nodo* actualColumna =cabeceraColumna->siguienteColumna;


    while (actualColumna != cabeceraColumna &&actualColumna != objetivo) {

        anteriorColumna = actualColumna;

        actualColumna =actualColumna->siguienteColumna;

    }


    if (actualColumna == objetivo) {

        anteriorColumna->siguienteColumna =objetivo->siguienteColumna;
    }


    delete objetivo;
}


// MOSTRAR

void Matriz::mostrar() {

    for (int fila = 0;fila < this->filas;fila++) {

        for (int columna = 0;columna < this->columnas;columna++) {


            Nodo* nodo =this->buscar(fila, columna);


            if (nodo == nullptr) {

                cout << "[-]";
            }

            else {

                cout << "["
                     << nodo->tipo
                     << "]";
            }
        }

        cout << endl;
    }
}


// MOSTRAR COMBATE

void Matriz::mostrarCombate() {

    for (int fila = 0;fila < this->filas;fila++) {

        for (int columna = 0;columna < this->columnas;columna++) {


            Nodo* nodo =this->buscar(fila, columna);


            if (nodo == nullptr) {

                cout << "[-]";
            }

            else if (nodo->tipo == "TJ") {

                cout << "[J]";
            }

            else if (nodo->tipo == "G") {

                cout << "[G]";
            }

            else if (nodo->tipo == "X") {

                cout << "[X]";
            }

            else {

                // TE permanece oculto

                cout << "[-]";
            }
        }

        cout << endl;
    }
}


// OBTENER FILAS

int Matriz::getFilas() {

    return this->filas;
}


// OBTENER COLUMNAS

int Matriz::getColumnas() {

    return this->columnas;
}


// LIBERAR

void Matriz::liberar() {

    if (this->cabecerasFila == nullptr) {

        return;
    }


    // RECORRER LAS FILAS

    for (int fila = 0;fila < this->filas;fila++) {


        Nodo* cabecera =this->cabecerasFila[fila];


        Nodo* actual =cabecera->siguienteFila;


        while (actual != cabecera) {

            Nodo* siguiente =actual->siguienteFila;


            delete actual;


            actual = siguiente;
        }


        cabecera->siguienteFila =cabecera;
    }


    // ELIMINAR CABECERAS DE FILAS

    for (int fila = 0;fila < this->filas;fila++) {

        delete this->cabecerasFila[fila];
    }


    // ELIMINAR CABECERAS DE COLUMNAS

    for (int columna = 0;columna < this->columnas;columna++) {

        delete this->cabecerasColumna[columna];
    }


    delete[] this->cabecerasFila;

    delete[] this->cabecerasColumna;


    this->cabecerasFila = nullptr;

    this->cabecerasColumna = nullptr;
}
