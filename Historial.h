#ifndef HISTORIAL_H
#define HISTORIAL_H

#include "RegistroTurno.h"

class Historial {

private:

    RegistroTurno* registros;

    int cantidad;

public:

    Historial();

    ~Historial();

    void agregar(const char* formaUtilizada,bool acerto,bool recibioDanio,int municionRecuperada);

    int getCantidad();

    RegistroTurno getRegistro(int posicion);

    void limpiar();
};

#endif
