#include <time.h>
#include "duerme.h"

void duerme(long nanosegundos) {
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = nanosegundos;

    nanosleep(&tim, &tim2);
}

void duerme_un_rato() {
    duerme(UN_RATO);
}

