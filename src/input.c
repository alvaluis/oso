#include <stdio.h>
#include "input.h"

/**
 * Pide un entero al usuario, hasta que este introduce
 * un valor válido (entre min y max).
 **/
int pedir_entero(const char *nombre, int min, int max) {
    int n;
    while (1) {
        printf("%s (%d-%d): ", nombre, min, max);
        scanf("%d%*c", &n);
        if (n >= min && n <= max)
            return n;
        else
            printf("Error: %s tiene que estar entre %d y %d\n", nombre, min, max);
    }
}

