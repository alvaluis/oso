#ifndef COLORS_H
#define COLORS_H

#define ANSI_COLOR_BLACK   "\x1b[30m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE   "\x1b[37m"
#define ANSI_COLOR_RESET   "\x1b[0m"

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
void printf_color(int color);

/*
 * void printf_reset_color();
 * Hace que el terminal a partir de ahora escriba en el color por defecto.
 */
void printf_reset_color();

#endif /* COLORS_H */

