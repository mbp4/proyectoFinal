//
// Created by Sira González-Madroño on 26/5/25.
//
// Archivo de cabecera para declarar las funciones que luego serán implementadas en el archivo utilidades.c

// Para evitar que el compilador lea el archivo más de una vez.
#ifndef PROYECTOFINAL_UTILIDADES_H
#define PROYECTOFINAL_UTILIDADES_H

// Declaraciones de funciones, solo incluye qué funciones existen y qué tipo de parámetros usan, pero no se define como están implementadas.
float** crear_matriz(int N);
void liberar_matriz(float** matriz, int N);
void inicializar_matriz(float** matriz, int N);
// Permite a otros archivos (como main.c o difusion_secuencial.c) usar estas funciones sin tener que saber cómo funcionan por dentro.

#endif
