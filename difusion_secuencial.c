//
// Created by Sira Gonzalez-Madroño on 26/5/25.
//
// Simulación secuencial de la difusión de calor en una placa metálica 2D.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "utilidades.h"

#define MAX(a,b) ((a) > (b) ? (a) : (b))

// Simular la difusión del calor en modo secuencial
// Se crean dos matrices
void difusion_secuencial(int N, float umbral, int max_iter) {
    float** actual = crear_matriz(N); // actual: contiene la temperatura actual en cada iteración.
    float** siguiente = crear_matriz(N); // siguiente: se usa para calcular las nuevas temperaturas.
    inicializar_matriz(actual, N); // Se inicializa la matriz actual: bordes a 100ºC, interior a 0ºC.

    int iter = 0; // iter: contador de iteraciones.
    float cambio_max; // cambio_max: guarda el mayor cambio de temperatura entre actual y siguiente en una iteración.
    double inicio = omp_get_wtime(); // omp_get_wtime(): función de OpenMP que obtiene el tiempo actual (para medir cuánto tarda la simulación).

    do {
        cambio_max = 0.0; // Reiniciamos cambio_max en cada iteración.

        for (int i = 1; i < N-1; i++) { // Este bucle actualiza los valores solo de las celdas interiores.
            for (int j = 1; j < N-1; j++) {
                siguiente[i][j] = 0.25 * (actual[i+1][j] + actual[i-1][j] + actual[i][j+1] + actual[i][j-1]); // La temperatura de cada celda se calcula como el promedio de sus 4 vecinas: arriba, abajo, izquierda y derecha.
                float cambio = fabs(siguiente[i][j] - actual[i][j]); // Se calcula el cambio de temperatura (fabs) con respecto a la anterior.
                cambio_max = MAX(cambio_max, cambio); // Se guarda el cambio máximo para usarlo como criterio de parada.
            }
        }

        // Copia los valores actualizados desde siguiente a actual para la siguiente iteración.
        for (int i = 1; i < N-1; i++) { // Solo se copian los valores interiores (los bordes siempre son 100 y no cambian).
            for (int j = 1; j < N-1; j++) {
                actual[i][j] = siguiente[i][j];
            }
        }
        iter++;
    } while (cambio_max > umbral && iter < max_iter); // El bucle se repite hasta que el cambio sea menor que el umbral, o hasta alcanzar max_iter iteraciones.

    double fin = omp_get_wtime(); // Calcula el tiempo total de ejecución de la simulación.
    printf("Secuencial: iteraciones = %d, tiempo = %.4f s\n", iter, fin - inicio); // Muestra cuántas iteraciones fueron necesarias.

    liberar_matriz(actual, N); // Libera la memoria reservada para ambas matrices.
    liberar_matriz(siguiente, N);
}
// Simula la difusión del calor sin paralelismo, usando una matriz NxN, hasta que:
// el cambio max de temperatura entre dos iteraciones consecutivas sea menor que el umbral, o
// se alcance el número max de iteraciones.