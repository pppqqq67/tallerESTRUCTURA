#ifndef MATRIZ_H
#define MATRIZ_H
#include <string>

using namespace std;

class Matriz {

public:

    struct Nodo {

        int fila;
        int columna;

        string tipo;

        bool descubierto;

        Nodo* siguienteFila;
        Nodo* siguienteColumna;


        Nodo(int fila, int columna, string tipo): fila(fila),columna(columna),tipo(tipo),descubierto(false),siguienteFila(this),siguienteColumna(this) {

        }
    };


private:

    int filas;
    int columnas;

    Nodo** cabecerasFila;
    Nodo** cabecerasColumna;


public:

    Matriz(int filas, int columnas);

    ~Matriz();


    void insertar(int fila, int columna, string tipo);

    Nodo* buscar(int fila, int columna);

    void eliminar(int fila, int columna);


    void mostrar();

    void mostrarCombate();


    int getFilas();

    int getColumnas();


    void liberar();


private:

    bool posicionValida(int fila, int columna) const;

};

#endif