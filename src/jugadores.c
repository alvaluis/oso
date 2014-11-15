#include <stdio.h>
#include "colores.h"
#include "jugadores.h"
#include "input.h"

void inicializar_jugadores(t_jugadores *js) {
    int i;

    js->num_jugadores = pedir_entero("","Numero de jugadores", MIN_JUGADORES, MAX_JUGADORES);
    js->num_humanos = pedir_entero("","Numero de jugadores humanos", MIN_HUMANOS, js->num_jugadores);

    js->turno = 0;
    for (i = 0; i < js->num_jugadores; i++)
        js->j[i].num_osos = 0;

    for (i = 0; i < js->num_humanos; i++)
        js->j[i].tipo = JUGADOR_HUMANO;
    for (i = js->num_humanos; i < js->num_jugadores; i++)
        js->j[i].tipo = JUGADOR_MAQUINA;
}

void pasar_turno(t_jugadores *js) {
    js->turno = (js->turno + 1) % js->num_jugadores;
}

void imprimir_jugador(int j) {
    printf_color(j);
    printf("[#%d]", j);
    printf_reset_color();
}

void imprimir_contadores(t_jugadores js) {
    int i;

    printf("OSOs:  ");
    for (i = 0; i < js.num_jugadores; i++) {
        imprimir_jugador(i);
        printf(": %d | ", js.j[i].num_osos);
    }
    printf("\n");
}

