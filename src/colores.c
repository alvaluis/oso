#include <stdio.h>
#include "colores.h"

/*
 * void printf_color(int color);
 * Dado un color:
 *
 *   -1: Reset
 *    0: Rojo
 *    1: Verde
 *    2: Amarillo
 *    3: Azul
 *    4: Magenta
 *    5: Cyan
 *
 * Hace que el terminal a partir de ahora escriba en ese color.
 */
void printf_color(int color) {
    switch (color) {
        case -1: printf(ANSI_COLOR_RESET ); break;
        case 0: printf(ANSI_COLOR_RED    ); break;
        case 1: printf(ANSI_COLOR_GREEN  ); break;
        case 2: printf(ANSI_COLOR_YELLOW ); break;
        case 3: printf(ANSI_COLOR_BLUE   ); break;
        case 4: printf(ANSI_COLOR_MAGENTA); break;
        case 5: printf(ANSI_COLOR_CYAN   ); break;
    }
}

/*
 * void printf_reset_color();
 * Hace que el terminal a partir de ahora escriba en el color por defecto.
 */
void printf_reset_color() {
    printf_color(-1);
}

