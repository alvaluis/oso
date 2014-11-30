#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
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

static struct termios inicial, actual;

static void signal_handler(int sig) {
    exit(1);
}

void inicializar_tty() {
    /* Por ahora no estamos interesados en comprobar
     * que los cambios en la TTY se efectuen. */
    tcgetattr(fileno(stdin), &inicial);
    memcpy(&actual, &inicial, sizeof(struct termios));

    atexit(restablecer_tty);
    signal(SIGTERM, signal_handler);
}

void adquirir_tty() {
    memcpy(&actual, &inicial, sizeof(struct termios));
    actual.c_lflag &= ~ICANON;
    actual.c_lflag &= ~ECHO;
    tcsetattr(fileno(stdin), TCSANOW, &actual);
}

void restablecer_tty() {
    memcpy(&actual, &inicial, sizeof(struct termios));
    tcsetattr(fileno(stdin), TCSANOW, &actual);
}
