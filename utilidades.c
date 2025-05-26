//
// Created by Sira González-Madroño on 26/5/25.
//
// Implementación real de las funciones declaradas en utilidades.h

#include <stdlib.h>  // Necesario para malloc y free.
#include "utilidades.h"  // Incluye las declaraciones de las funciones.

// Crear una matriz dinámica NxN
float** crear_matriz(int N) {
    float** matriz = malloc(N * sizeof(float*));
    for (int i = 0; i < N; i++){
        matriz[i] = malloc(N * sizeof(float));
    }
    return matriz;
}
// Usa malloc para reservar un array de N punteros a filas float**.
// Para cada fila reserva N elementos float.
// Devuelve un puntero doble float** que apunta a toda la matriz.

// Liberar la memoria de la matriz
void liberar_matriz(float** matriz, int N) {
    for (int i = 0; i < N; i++) {
        free(matriz[i]);
    }
    free(matriz);
}
// Libera la memoria que se había reservado con crear_matriz.
// Primero libera cada fila individualmente con matriz[i], y luego libera el array de punteros.

// Inicializar la matriz: bordes a 100ºC, interior a 0ºC
void inicializar_matriz(float** matriz, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == 0 || i == N-1 || j == 0 || j == N-1)
                matriz[i][j] = 100.0;
            else
                matriz[i][j] = 0.0;
        }
    }
}
// Inicializa la matriz con los valores pedidos en el enunciado.
// Bordes (filas y columnas de los extremos): se ponen a 100.0 (simulan una fuente de calor).
// Interior: se pone a 0.0 (temperatura inicial sin calor).
// Usa un doble bucle for para recorrer todos los elementos.
