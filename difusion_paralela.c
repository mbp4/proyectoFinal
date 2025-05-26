//
// Created by Miriam Blanco Ponce on 26/5/25.
//
// Simulación Paralela de la difusión del calor en una superficie bidimensional
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include "utilidades.h" //importamos nuestras funciones para poder crear, inicializar, liberar y usar la matriz

#define MAX(a,b) ((a) > (b) ? (a) : (b))

void difusion_paralela(int N, float umbral, int max_iter) {
    float** actual = crear_matriz(N);
    float** siguiente = crear_matriz(N);
    //creamos dos matrices una para guardar los valores actuales y otra para los siguientes valores obtenidos
    inicializar_matriz(actual, N);
    //inicializamos la matriz con los valores pedidos en el enunciado

    int iter = 0; //contador de iteraciones
    float cambio_max; //guarda el máximo cambio de temperatura entre iteracciones
    double inicio = omp_get_wtime(); //función de OpenMP para medir el tiempo que tarda la simulación

    do {
        cambio_max = 0.0; //este se reiniciará cada vez que se llegué al máximo de iteraciones


        //bucle paralelo para actualizar los valores de "siguiente" y calcular el cambio de temperatura haciendo uso de reduction
#pragma omp parallel for reduction(max:cambio_max) collapse(2)
        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < N - 1; j++) {
                siguiente[i][j] = 0.25 * (actual[i+1][j] + actual[i-1][j] + actual[i][j+1] + actual[i][j-1]);
                float cambio = fabs(siguiente[i][j] - actual[i][j]);
                cambio_max = MAX(cambio_max, cambio);
            }
        }

        //copia los valores calculados de "siguiente" a la "actual" para las proximas iteraciones
#pragma omp parallel for collapse(2)
        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < N - 1; j++) {
                actual[i][j] = siguiente[i][j];
            }
        }

        iter++;
    } while (cambio_max > umbral && iter < max_iter);

    double fin = omp_get_wtime(); //obtenemos el tiempo final
    printf("Paralela: iteraciones = %d, tiempo = %.4f s\n", iter, fin - inicio); //mostramos cuantas iteraciones se realizaron y el tiempo total

    //liberamos la memoria reservada para ambas matrices
    liberar_matriz(actual, N);
    liberar_matriz(siguiente, N);
}
