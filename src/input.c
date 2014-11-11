#include <stdio.h>
#include "input.h"

/**
 * Pide un entero al usuario, hasta que este introduce
 * un valor válido (entre min y max).
 **/
int pedir_entero(const char *prefijo, const char *nombre, int min, int max) {
    int n, r;
    while (1) {
        printf("%s%s (%d-%d): ", prefijo, nombre, min, max);
        r = scanf("%d%*c", &n);
        if (r == 1 && n >= min && n <= max)
            return n;
        else
            printf("Error: %s tiene que estar entre %d y %d\n", nombre, min, max);
    }
}

