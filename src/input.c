#include <stdio.h>
#include "input.h"

void descartar_linea() {
    scanf("%*[^\n]");
    scanf("%*c");
}

int pedir_entero(const char *prefijo, const char *nombre, int min, int max) {
    int n, r;
    while (1) {
        printf("%s%s (%d-%d): ", prefijo, nombre, min, max);
        r = scanf("%d", &n);
        descartar_linea();

        if (r == 1 && n >= min && n <= max)
            return n;
        else
            printf("Error: %s tiene que estar entre %d y %d\n", nombre, min, max);
    }
}

