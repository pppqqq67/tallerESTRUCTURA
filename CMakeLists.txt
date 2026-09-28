cmake_minimum_required(VERSION 4.3)
project(untitledproject)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitledproject main.cpp
        MatriZ.cpp
        MatriZ.h
        Forma.cpp
        Forma.h
        Historial.cpp
        Historial.h
        Juego.cpp
        Juego.h
        LecturaArchivo.cpp
        LecturaArchivo.h
        Coordenada.cpp
        Coordenada.h
        RegistroTurno.h
)
