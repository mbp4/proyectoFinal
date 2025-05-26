#include <stdio.h>
#include <stdlib.h>

// Declaración de la función secuencial
void difusion_secuencial(int N, float umbral, int max_iter);
void difusion_paralela(int N, float umbral, int max_iter);

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Uso: %s <N> <umbral> <max_iter>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    float umbral = atof(argv[2]);
    int max_iter = atoi(argv[3]);

    printf("Ejecutando simulación secuencial...\n");
    difusion_secuencial(N, umbral, max_iter);

    printf("Ejecutando simulación paralela con OpenMP...\n");
    difusion_paralela(N, umbral, max_iter);

    return 0;
}

