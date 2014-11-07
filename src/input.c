#include <stdio.h>
#include "input.h"

int pedir_campo(const char *nombre, int min, int max) {
    int n;
    while(1){
        printf("%s (%d-%d): ", nombre, min, max);
        scanf("%d%*c", &n);
        if(n >= min && n <= max)
            return n;
        else
            printf("Error: %s tiene que estar entre %d y %d\n", nombre, min, max);
    }    
}

