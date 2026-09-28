#include "LecturaArchivo.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

namespace LecturaArchivos {

    // CARGAR FORMAS
    bool cargarFormas(const string& path,Forma formas[5]) {

        ifstream archivo(path);

        if (!archivo.is_open()) {

            cout << "No se pudo abrir el archivo: "
                 << path << endl;

            return false;
        }

        cout << "formas.txt abierto correctamente."
             << endl;


        string linea;

        int posicion = 0;


        while (getline(archivo, linea)) {

            if (linea.empty()) {
                continue;
            }

            stringstream ss(linea);

            string nombre;

            getline(ss,nombre,';');

            formas[posicion].setNombre(nombre);

            string coordenada;

            while (getline(ss,coordenada,';')) {

                stringstream ssCoordenada(coordenada);

                string filaTexto;
                string columnaTexto;

                getline(ssCoordenada,filaTexto,',');

                getline(ssCoordenada,columnaTexto);

                int fila = stoi(filaTexto);
                int columna = stoi(columnaTexto);


                formas[posicion].agregarCoordenada(fila,columna);
            }

            posicion++;

            if (posicion == 5) {
                break;
            }
        }


        archivo.close();


        if (posicion != 5) {

            cout << "No se encontraron las 5 formas."
                 << endl;

            return false;
        }


        return true;
    }


    // CARGAR CAMPO DE BATALLA
    bool cargarCampo(const string& path,Matriz& matriz) {

        ifstream archivo(path);

        if (!archivo.is_open()) {

            cout << "No se pudo abrir el archivo: "
                 << path << endl;

            return false;
        }


        string linea;


        while (getline(archivo, linea)) {

            if (linea.empty()) {
                continue;
            }


            stringstream ss(linea);


            string tipo;
            string filaTexto;
            string columnaTexto;


            getline(ss,tipo,',');


            getline(ss,filaTexto,',');


            getline(ss,columnaTexto);


            int fila = stoi(filaTexto);

            int columna = stoi(columnaTexto);


            matriz.insertar(fila,columna,tipo);

        }

        archivo.close();

        return true;
    }

}
