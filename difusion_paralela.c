//
// Created by Miriam Blanco Ponce on 26/5/25.
//
// Simulación Paralela de la difusión del calor en una superficie bidimensional
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include "utilidades.h"

#define MAX(a,b) ((a) > (b) ? (a) : (b))

void difusion_paralela(int N, float umbral, int max_iter) {
    float** actual = crear_matriz(N);
    float** siguiente = crear_matriz(N);
    inicializar_matriz(actual, N);

    int iter = 0;
    float cambio_max;
    double inicio = omp_get_wtime();

    do {
        cambio_max = 0.0;


#pragma omp parallel for reduction(max:cambio_max) collapse(2)
        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < N - 1; j++) {
                siguiente[i][j] = 0.25 * (actual[i+1][j] + actual[i-1][j] + actual[i][j+1] + actual[i][j-1]);
                float cambio = fabs(siguiente[i][j] - actual[i][j]);
                cambio_max = MAX(cambio_max, cambio);
            }
        }

#pragma omp parallel for collapse(2)
        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < N - 1; j++) {
                actual[i][j] = siguiente[i][j];
            }
        }

        iter++;
    } while (cambio_max > umbral && iter < max_iter);

    double fin = omp_get_wtime();
    printf("Paralela: iteraciones = %d, tiempo = %.4f s\n", iter, fin - inicio);

    liberar_matriz(actual, N);
    liberar_matriz(siguiente, N);
}
