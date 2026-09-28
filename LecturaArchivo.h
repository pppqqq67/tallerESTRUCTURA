#ifndef LECTURAARCHIVO_H
#define LECTURAARCHIVO_H
#include <string>
#include "Forma.h"
#include "Matriz.h"


using namespace std;

namespace LecturaArchivos {

    bool cargarFormas(const string& path,Forma formas[5]);

    bool cargarCampo(const string& path,Matriz& matriz);

}

#endif
