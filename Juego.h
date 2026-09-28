#ifndef JUEGO_H
#define JUEGO_H
#include "Matriz.h"
#include "Forma.h"
#include "RegistroTurno.h"

#include <string>

using namespace std;

class Juego {

private:

    // CAMPO DE BATALLA
    Matriz* campo;


    // CONFIGURACION
    int dificultad;

    int tamanioMapa;

    int cantidadGeneradores;

    int municionInicial;


    // ESTADO DE PARTIDA
    bool partidaPreparada;

    int turno;

    int generadoresDestruidos;

    int municionRecuperada;

    bool combateTerminado;


    // ARREGLO ESTATICO DE FORMAS
    Forma formas[5];


    // ARREGLO DINAMICO
    // HISTORIAL DE TURNOS
    RegistroTurno* historialTurnos;

    int cantidadTurnos;


    // ESTADO DEL TURNO ACTUAL
    bool turnoAcerto;

    bool turnoRecibioDanio;

    int turnoMunicionRecuperada;


public:

    // CONSTRUCTOR / DESTRUCTOR
    Juego();

    ~Juego();


    // MENU
    void iniciar();

    void menuPrincipal();

    void prepararPartida();

    void elegirDificultad();

    void verCampo();


    // COMBATE
    void iniciarCombate();

    void mostrarTurno();

    void mostrarMunicion();

    void disparar();


    // DISPARO
    bool aplicarDisparo(int indiceForma,int fila,int columna,bool jugador);


    // CPU
    void turnoCPU();


    // VICTORIA / DERROTA
    bool verificarVictoria();

    bool verificarDerrota();


    void finalizarPartida(bool victoria,string motivo);


    // HISTORIAL
    void registrarTurno();

    void mostrarHistorial();


    // LIMPIEZA
    void limpiarPartida();
};

#endif