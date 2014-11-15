#ifndef AZAR_H
#define AZAR_H

/*
 * void inicializar_azar();
 * Se tiene que ejecutar una vez al principio del programa
 * para inicializar la generación de números aleatorios.
 */
void inicializar_azar();

/*
 * int numero_al_azar(int max);
 * Devuelve un número entero al azar entre [1, max].
 */
int numero_al_azar(int max);

/*
 * int indice_al_azar(int cantidad);
 * Devuelve un índice aleatorio, es decir, un entero entre [0, cantidad).
 */
int indice_al_azar(int cantidad);

#endif /* AZAR_H */

