#include <time.h>	// time()
#include <stdlib.h>	// rand(), srand()
#include <stdio.h>	// printf()
#include "azar.h"

/*
 * void inicializar_azar();
 * Se tiene que ejecutar una vez al principio del programa
 * para inicializar la generación de números aleatorios.
 */
void inicializar_azar() {
    /*
     * Para que la sequencia de numeros aleatorios sea igual en cada
     * ejecucion usad el srand (0) en lugar del srand(time).
     */
    //srand(0);
    srand((unsigned) time(NULL));
}

/*
 * int numero_al_azar(int max);
 * Devuelve un número entero al azar entre [1, max].
 */
int numero_al_azar(int max) {
    return (rand() % max) + 1;
}

/*
 * int indice_al_azar(int cantidad);
 * Devuelve un índice aleatorio, es decir, un entero entre [0, cantidad).
 */
int indice_al_azar(int cantidad) {
    return rand() % cantidad;
}

