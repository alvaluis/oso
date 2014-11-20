#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include "azar.h"

void inicializar_azar() {
    /*
     * Para que la sequencia de numeros aleatorios sea igual en cada
     * ejecucion usad el srand (0) en lugar del srand(time).
     */
    //srand(0);
    struct timeval time;
    gettimeofday(&time, NULL);
    srand(time.tv_sec * 1e2 + time.tv_usec / 1e4);
}

int numero_al_azar(int max) {
    return (rand() % max) + 1;
}

int indice_al_azar(int cantidad) {
    return rand() % cantidad;
}

