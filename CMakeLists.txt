cmake_minimum_required(VERSION 3.30.5)
project(proyectoFinal C)

set(CMAKE_C_STANDARD 11)

add_executable(proyectoFinal main.c
        utilidades.c
        utilidades.h
        difusion_secuencial.c)
