#ifndef DUERME_H
#define DUERME_H

#define UN_RATO	50e6	// 50 milisegundos

/*
 * void duerme(long nanosegundos);
 * Hace que la ejecucion del programa se detenga durante
 * el numero de nanosegundos que se le pasa por parametro
 */
void duerme(long nanosegundos);

/*
 * void duerme_un_rato();
 * Hace que la ejecucion del programa se detenga durante
 * un numero de nanosegundos predeterminado
 */
void duerme_un_rato();

#endif /* DUERME_H */

