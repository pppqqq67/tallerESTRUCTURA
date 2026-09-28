#include "Juego.h"
#include "LecturaArchivo.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

// CONSTRUCTOR

Juego::Juego() {

    this->campo = nullptr;

    this->dificultad = 0;
    this->tamanioMapa = 0;
    this->cantidadGeneradores = 0;
    this->municionInicial = 0;

    this->partidaPreparada = false;

    this->turno = 0;
    this->generadoresDestruidos = 0;
    this->municionRecuperada = 0;
    this->combateTerminado = false;

    this->historialTurnos = nullptr;
    this->cantidadTurnos = 0;

    this->turnoAcerto = false;
    this->turnoRecibioDanio = false;
    this->turnoMunicionRecuperada = 0;

    srand(time(nullptr));
}

// DESTRUCTOR

Juego::~Juego() {

    this->limpiarPartida();
}

// INICIAR

void Juego::iniciar() {

    this->menuPrincipal();
}

// MENU PRINCIPAL

void Juego::menuPrincipal() {

    int opcion;

    do {

        cout << endl;
        cout << "=========================" << endl;
        cout << "  War. War Never Changes" << endl;
        cout << "=========================" << endl;

        cout << "1. Preparar partida" << endl;
        cout << "2. Iniciar combate" << endl;
        cout << "3. Ver estadisticas" << endl;
        cout << "4. Salir" << endl;

        cout << "=========================" << endl;
        cout << "Seleccione una opcion: ";

        cin >> opcion;


        switch (opcion) {

            case 1:

                this->prepararPartida();

                break;


            case 2:

                if (!this->partidaPreparada) {

                    cout << endl;
                    cout << "Debe preparar una partida primero."
                         << endl;

                } else {

                    this->iniciarCombate();
                }

                break;


            case 3:

                this->mostrarHistorial();

                break;


            case 4:

                cout << endl;
                cout << "Saliendo del juego..."
                     << endl;

                break;


            default:

                cout << endl;
                cout << "Opcion invalida."
                     << endl;
        }

    } while (opcion != 4);
}



// PREPARAR PARTIDA

void Juego::prepararPartida() {

    int opcion;

    do {

        cout << endl;
        cout << "==== PREPARAR PARTIDA ===="
             << endl;

        cout << "1. Elegir dificultad" << endl;
        cout << "2. Ver campo de batalla" << endl;
        cout << "3. Volver al menu principal" << endl;

        cout << "Seleccione una opcion: ";

        cin >> opcion;


        switch (opcion) {

            case 1:

                this->elegirDificultad();

                break;


            case 2:

                this->verCampo();

                break;


            case 3:

                cout << "Volviendo al menu principal..."
                     << endl;

                break;


            default:

                cout << "Opcion invalida."
                     << endl;
        }

    } while (opcion != 3);
}

// ELEGIR DIFICULTAD

void Juego::elegirDificultad() {

    int opcion;

    cout << endl;
    cout << "==== ELEGIR DIFICULTAD ===="
         << endl;

    cout << "1. Facil" << endl;
    cout << "2. Media" << endl;
    cout << "3. Dificil" << endl;

    cout << "Seleccione una opcion: ";

    cin >> opcion;


    if (
        opcion < 1 ||
        opcion > 3
    ) {

        cout << "Opcion invalida."
             << endl;

        return;
    }

    // LIMPIAR PARTIDA ANTERIOR

    this->limpiarPartida();

    // CONFIGURAR DIFICULTAD

    switch (opcion) {

        case 1:

            this->dificultad = 1;
            this->tamanioMapa = 30;
            this->cantidadGeneradores = 5;
            this->municionInicial = 8;

            break;


        case 2:

            this->dificultad = 2;
            this->tamanioMapa = 50;
            this->cantidadGeneradores = 10;
            this->municionInicial = 6;

            break;


        case 3:

            this->dificultad = 3;
            this->tamanioMapa = 100;
            this->cantidadGeneradores = 20;
            this->municionInicial = 5;

            break;
    }


    // CREAR CAMPO

    this->campo =new Matriz(this->tamanioMapa,this->tamanioMapa);


    // CARGAR FORMAS

    bool formasCargadas =LecturaArchivos::cargarFormas("formas.txt",this->formas);


    if (!formasCargadas) {

        cout << "No se pudieron cargar las formas."
             << endl;

        this->limpiarPartida();

        return;
    }


    // ASIGNAR MUNICION

    for (int i = 0; i < 5; i++) {

        this->formas[i].setMunicion(this->municionInicial);
    }


    // CARGAR CAMPO

    bool campoCargado = false;


    if (this->dificultad == 1) {

        campoCargado =LecturaArchivos::cargarCampo("campoF.txt",*this->campo);
    }

    else if (this->dificultad == 2) {

        campoCargado =LecturaArchivos::cargarCampo("campoM.txt",*this->campo);
    }

    else if (this->dificultad == 3) {

        campoCargado =LecturaArchivos::cargarCampo("campoD.txt",*this->campo);
    }


    if (!campoCargado) {

        cout << "No se pudo cargar el campo de batalla."
             << endl;

        this->limpiarPartida();

        return;
    }

    // INICIALIZAR ESTADO

    this->turno = 0;

    this->generadoresDestruidos = 0;

    this->municionRecuperada = 0;

    this->combateTerminado = false;

    this->partidaPreparada = true;


    cout << endl;
    cout << "¡Torreta lista para el combate!"
         << endl;

    cout << "Tamano del mapa: "
         << this->tamanioMapa
         << "x"
         << this->tamanioMapa
         << endl;

    cout << "Generadores necesarios: "
         << this->cantidadGeneradores
         << endl;

    cout << "Municion disponible:"
         << endl;


    for (int i = 0; i < 5; i++) {

        cout << "- "
             << this->formas[i].getNombre()
             << ": "
             << this->formas[i].getMunicion()
             << endl;
    }
}

// VER CAMPO

void Juego::verCampo() {

    if (!this->partidaPreparada) {

        cout << endl;
        cout << "Primero debe elegir una dificultad."
             << endl;

        return;
    }


    cout << endl;
    cout << "==== CAMPO DE BATALLA ===="
         << endl;

    this->campo->mostrar();
}

// INICIAR COMBATE

void Juego::iniciarCombate() {

    this->turno = 1;

    this->generadoresDestruidos = 0;

    this->municionRecuperada = 0;

    this->combateTerminado = false;


    // LIMPIAR HISTORIAL

    if (this->historialTurnos != nullptr) {

        free(this->historialTurnos);

        this->historialTurnos = nullptr;
    }

    this->cantidadTurnos = 0;


    int opcion;


    while (!this->combateTerminado) {

        this->mostrarTurno();

        cin >> opcion;


        switch (opcion) {

            case 1:

                this->disparar();

                break;


            case 2: {

                char respuesta;

                cout << endl;

                cout << "¿Esta seguro de que desea abandonar "
                     << "la partida actual? (S/N): ";

                cin >> respuesta;


                if (
                    respuesta == 'S' ||
                    respuesta == 's'
                ) {

                    cout << endl;
                    cout << "Partida abandonada."
                         << endl;

                    this->limpiarPartida();

                    return;
                }

                break;
            }


            default:

                cout << "Opcion invalida."
                     << endl;
        }
    }
}

// MOSTRAR TURNO

void Juego::mostrarTurno() {

    cout << endl;

    cout << "--- TURNO "
         << this->turno
         << " | CAMPO DE BATALLA ("
         << this->tamanioMapa
         << "x"
         << this->tamanioMapa
         << ") ---"
         << endl;


    this->campo->mostrarCombate();


    cout << endl;

    this->mostrarMunicion();


    cout << endl;

    cout << "========================================="
         << endl;

    cout << "--- ACCIONES DISPONIBLES ---"
         << endl;

    cout << "1. Disparar" << endl;
    cout << "2. Salir al Menu Principal" << endl;

    cout << "Seleccione una opcion: ";
}


// MOSTRAR MUNICION

void Juego::mostrarMunicion() {

    cout << "--- ESTADO DEL CARGADOR ---"
         << endl;


    for (int i = 0; i < 5; i++) {

        cout << i + 1
             << ". "
             << this->formas[i].getNombre()
             << " : "
             << this->formas[i].getMunicion()
             << "/"
             << this->municionInicial
             << " disp."
             << endl;
    }
}


// DISPARAR

void Juego::disparar() {

    cout << endl;

    cout << "========================================="
         << endl;

    cout << "              DISPARAR"
         << endl;

    cout << "========================================="
         << endl;


    this->mostrarMunicion();


    int opcion;

    cout << endl;
    cout << "Seleccione la forma: ";

    cin >> opcion;


    if (opcion < 1 ||opcion > 5) {

        cout << "Forma invalida."
             << endl;

        return;
    }


    int indiceForma = opcion - 1;


    if (this->formas[indiceForma].getMunicion() <= 0) {

        cout << "No queda municion de esta forma."
             << endl;

        return;
    }


    int fila;
    int columna;


    cout << "Ingrese fila: ";
    cin >> fila;

    cout << "Ingrese columna: ";
    cin >> columna;


    // CASO 0,0

    if (fila < 0 ||fila >= this->tamanioMapa ||columna < 0 ||columna >= this->tamanioMapa) {

        cout << "Coordenada fuera del mapa."
             << endl;

        return;
    }


    cout << endl;

    cout << "--- CAMPO ANTES DEL DISPARO ---"
         << endl;

    this->campo->mostrarCombate();


    // REINICIAR ESTADO DEL TURNO

    this->turnoAcerto = false;

    this->turnoRecibioDanio = false;

    this->turnoMunicionRecuperada = 0;


    // APLICAR DISPARO

    this->turnoAcerto =this->aplicarDisparo(indiceForma,fila,columna,true);


    // GASTAR MUNICION

    this->formas[indiceForma].restarMunicion();


    cout << endl;

    cout << "--- CAMPO DESPUES DEL DISPARO ---"
         << endl;

    this->campo->mostrarCombate();

    // TURNO CPU

    bool victoria =this->verificarVictoria();


    if (victoria) {

        this->registrarTurno();

        return;
    }


    cout << endl;

    cout << "--- TURNO DE LA CPU ---"
         << endl;

    this->turnoCPU();


    // VERIFICAR RESULTADO

    victoria =this->verificarVictoria();


    if (victoria) {

        this->registrarTurno();

        return;
    }


    bool derrota =this->verificarDerrota();


    // GUARDAR HISTORIAL

    this->registrarTurno();


    if (derrota) {

        return;
    }


    this->turno++;
}


// APLICAR DISPARO


bool Juego::aplicarDisparo(int indiceForma,int fila,int columna,bool jugador) {

    Forma& forma =this->formas[indiceForma];

    bool acierto = false;


    cout << endl;

    cout << "Impactando con forma: "
         << forma.getNombre()
         << endl;


    for (int i = 0;i < forma.getCantidadImpactos();i++) {

        Coordenada coordenada =forma.getCoordenada(i);


        int nuevaFila =fila + coordenada.getFila();


        int nuevaColumna =columna + coordenada.getColumna();


        // FUERA DEL MAPA

        if (nuevaFila < 0 ||nuevaFila >= this->tamanioMapa ||nuevaColumna < 0 ||nuevaColumna >= this->tamanioMapa) {

            continue;
        }


        Matriz::Nodo* nodo =this->campo->buscar(nuevaFila,nuevaColumna);


        // CELDA VACIA

        if (nodo == nullptr) {

            this->campo->insertar(nuevaFila,nuevaColumna,"X");

            continue;
        }


        string tipo =nodo->tipo;


        // GENERADOR


        if (tipo == "GE") {

            acierto = true;

            cout << "¡Generador destruido en ("
                 << nuevaFila
                 << ", "
                 << nuevaColumna
                 << ")!"
                 << endl;


            this->campo->eliminar(nuevaFila,nuevaColumna);


            this->generadoresDestruidos++;

            forma.agregarMunicion();

            this->municionRecuperada++;

            this->turnoMunicionRecuperada++;


            cout << "Municion recuperada: "
                 << forma.getNombre()
                 << " +1"
                 << endl;


            continue;
        }


        // TORRETA ENEMIGA

        if (tipo == "TE") {

            acierto = true;

            cout << endl;

            cout << "¡TORRETA ENEMIGA DESTRUIDA!"
                 << endl;


            this->campo->eliminar(nuevaFila,nuevaColumna);

            continue;
        }


        // TORRETA JUGADOR

        if (tipo == "TJ") {

            if (jugador) {

                cout << "La torreta del jugador "
                     << "esta protegida durante "
                     << "su propio turno."
                     << endl;
            }

            continue;
        }


        // CELDA YA IMPACTADA


        if (tipo == "X") {

            continue;
        }
    }


    return acierto;
}


// TURNO CPU

void Juego::turnoCPU() {

    int fila =rand() % this->tamanioMapa;

    int columna =rand() % this->tamanioMapa;

    int indiceForma =rand() % 5;


    cout << "La CPU dispara en ("
         << fila
         << ", "
         << columna
         << ")"
         << endl;


    cout << "Forma de la CPU: "
         << this->formas[indiceForma].getNombre()
         << endl;


    Matriz::Nodo* nodo =
        this->campo->buscar(
            fila,
            columna
        );


    // TORRETA DEL JUGADOR

    if (nodo != nullptr &&nodo->tipo == "TJ") {

        this->turnoRecibioDanio = true;


        cout << "Torreta dañada, se perdieron "
             << "municiones de la reserva."
             << endl;


        int perdidas = 0;


        while (perdidas < 2) {int municion = rand() % 5;


            if (this->formas[municion].getMunicion() > 0) {

                this->formas[municion].restarMunicion();

                perdidas++;
            }


            int total = 0;


            for (int i = 0; i < 5; i++) {

                total +=this->formas[i].getMunicion();
            }


            if (total == 0) {

                break;
            }
        }


        return;
    }


    // GENERADOR

    if (nodo != nullptr &&nodo->tipo == "GE"
    ) {

        cout << "La CPU destruyo un generador."
             << endl;


        this->campo->eliminar(fila,columna);


        this->generadoresDestruidos++;


        cout << "El generador destruido por "
             << "la CPU cuenta para la meta."
             << endl;


        return;
    }


    cout << "El disparo de la CPU no tuvo efecto."
         << endl;
}


// VERIFICAR VICTORIA

bool Juego::verificarVictoria() {

    bool existeTorreta = false;


    for (int fila = 0;fila < this->tamanioMapa;fila++) {

        for (int columna = 0;columna < this->tamanioMapa;columna++) {

            Matriz::Nodo* nodo =this->campo->buscar(fila,columna);


            if (nodo != nullptr &&nodo->tipo == "TE") {

                existeTorreta = true;

                break;
            }
        }


        if (existeTorreta) {

            break;
        }
    }


    // TORRETA DESTRUIDA


    if (!existeTorreta) {

        this->finalizarPartida(true,"destruccion de la torreta enemiga");

        return true;
    }


    // GENERADORES

    if (this->generadoresDestruidos >=this->cantidadGeneradores
    ) {

        this->finalizarPartida(true,"cantidad de generadores alcanzada");

        return true;
    }


    return false;
}


// VERIFICAR DERROTA

bool Juego::verificarDerrota() {

    int total = 0;


    for (int i = 0; i < 5; i++) {
        total +=this->formas[i].getMunicion();
    }


    if (total <= 0) {

        this->finalizarPartida(false,"sin municion");

        return true;
    }


    return false;
}

// REGISTRAR TURNO

void Juego::registrarTurno() {

    RegistroTurno* nuevoHistorial =(RegistroTurno*) realloc(this->historialTurnos,(this->cantidadTurnos + 1)* sizeof(RegistroTurno));


    if (nuevoHistorial == nullptr) {

        cout << "Error al ampliar el historial."
             << endl;

        return;
    }


    this->historialTurnos =nuevoHistorial;


    RegistroTurno& registro =this->historialTurnos[this->cantidadTurnos];


    // FORMA UTILIZADA

    strcpy(registro.formaUtilizada,"No registrada");


    registro.acerto =this->turnoAcerto;


    registro.recibioDanio =this->turnoRecibioDanio;


    registro.municionRecuperada =this->turnoMunicionRecuperada;


    this->cantidadTurnos++;
}



// MOSTRAR HISTORIAL

void Juego::mostrarHistorial() {

    cout << endl;

    cout << "========================================="
         << endl;

    cout << "         HISTORIAL DE TURNOS"
         << endl;

    cout << "========================================="
         << endl;


    if (this->historialTurnos == nullptr ||this->cantidadTurnos == 0) {

        cout << "No existen turnos registrados."
             << endl;

        return;
    }


    for (int i = 0;i < this->cantidadTurnos;i++) {

        RegistroTurno& registro =this->historialTurnos[i];


        cout << endl;

        cout << "--- TURNO "
             << i + 1
             << " ---"
             << endl;


        cout << "Forma utilizada: "
             << registro.formaUtilizada
             << endl;


        cout << "Acerto: "
             << (
                 registro.acerto
                 ? "SI"
                 : "NO"
             )
             << endl;


        cout << "Recibio dano: "
             << (
                 registro.recibioDanio
                 ? "SI"
                 : "NO"
             )
             << endl;


        cout << "Municion recuperada: "
             << registro.municionRecuperada
             << endl;
    }
}


// FINALIZAR PARTIDA

void Juego::finalizarPartida(bool victoria,string motivo) {

    this->combateTerminado = true;


    cout << endl;

    cout << "=================================================="
         << endl;


    if (victoria) {

        cout << "                 ¡VICTORIA!"
             << endl;

        cout << "Motivo: "
             << motivo
             << endl;
    }

    else {

        cout << "                 DERROTA"
             << endl;

        cout << "Torreta sin municion, incapaz de completar "
             << "la mision."
             << endl;
    }


    cout << "Generadores destruidos: "
         << this->generadoresDestruidos
         << " de "
         << this->cantidadGeneradores
         << endl;


    cout << "Turno de finalizacion: "
         << this->turno
         << endl;


    cout << "Municion recuperada: "
         << this->municionRecuperada
         << endl;


    cout << "=================================================="
         << endl;
}



// LIMPIAR PARTIDA

void Juego::limpiarPartida() {

    // CAMPO
    if (this->campo != nullptr) {

        delete this->campo;

        this->campo = nullptr;
    }


    // HISTORIAL
    if (this->historialTurnos != nullptr) {

        free(this->historialTurnos);

        this->historialTurnos = nullptr;
    }


    this->cantidadTurnos = 0;


    // CONFIGURACION
    this->dificultad = 0;

    this->tamanioMapa = 0;

    this->cantidadGeneradores = 0;

    this->municionInicial = 0;


    // ESTADO
    this->partidaPreparada = false;

    this->turno = 0;

    this->generadoresDestruidos = 0;

    this->municionRecuperada = 0;

    this->combateTerminado = false;


    this->turnoAcerto = false;

    this->turnoRecibioDanio = false;

    this->turnoMunicionRecuperada = 0;
}
