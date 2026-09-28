// Created by bip

#ifndef COORDENADA_H
#define COORDENADA_H

class Coordenada {

private:

    int fila;
    int columna;

public:

    Coordenada();
    Coordenada(int fila, int columna);

    int getFila();
    int getColumna();

    void setFila(int fila);
    void setColumna(int columna);
};

#endif