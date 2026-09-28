// Created by bip

#include "Coordenada.h"

// CONSTRUCTOR VACIO

Coordenada::Coordenada() {

    this->fila = 0;
    this->columna = 0;
}

// CONSTRUCTOR

Coordenada::Coordenada(int fila,int columna) {
    this->fila = fila;
    this->columna = columna;
}

// GET FILA

int Coordenada::getFila() {

    return this->fila;
}

// GET COLUMNA

int Coordenada::getColumna() {

    return this->columna;
}

// SET FILA

void Coordenada::setFila(int fila) {

    this->fila = fila;
}

// SET COLUMNA

void Coordenada::setColumna(int columna) {

    this->columna = columna;
}