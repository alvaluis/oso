#include <time.h>
#include "duerme.h"

/*
 * void duerme(long nanosegundos);
 * Hace que la ejecucion del programa se detenga durante
 * el numero de nanosegundos que se le pasa por parametro
 */
void duerme(long nanosegundos) {
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = nanosegundos;

    nanosleep(&tim, &tim2);
}

/*
 * void duerme_un_rato();
 * Hace que la ejecucion del programa se detenga durante
 * un numero de nanosegundos predeterminado
 */
void duerme_un_rato() {
    duerme(UN_RATO);
}

