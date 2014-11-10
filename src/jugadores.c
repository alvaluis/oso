#include <stdio.h>
#include "colores.h"
#include "jugadores.h"
#include "input.h"

/*
 * void inicializar_jugadores(t_jugadores *js);
 * Dado un puntero a jugadores los inicializa pidiendo al usuario el numero
 * de jugadores y el de jugadores humanos, assegurandose que ambos estan
 * entre el numero de jugadores minimo y maximo permitidos.
 * E inicializa el turno al primer jugador.
 */
void inicializar_jugadores(t_jugadores *js) {
    int i;

    js->num_jugadores = pedir_entero("Numero de jugadores", MIN_JUGADORES, MAX_JUGADORES);
    js->num_humanos = pedir_entero("Numero de jugadores humanos", MIN_HUMANOS, js->num_jugadores);

    js->turno = 0;
    for (i = 0; i < js->num_jugadores; i++)
        js->j[i].num_osos = 0;

    for (i = 0; i < js->num_humanos; i++)
        js->j[i].tipo = JUGADOR_HUMANO;
    for (i = js->num_humanos; i < js->num_jugadores; i++)
        js->j[i].tipo = JUGADOR_MAQUINA;
}

/*
 * void pasar_turno(t_jugadores *js);
 * Dado un puntero a jugadores pasa el turno al siguiente jugador
 */
void pasar_turno(t_jugadores *js) {
    js->turno = (js->turno + 1) % js->num_jugadores;
}

/*
 * Dado un entero 'j' (correspondiente al jugador numero 'j',
 * imprime en el color 'j' la cadena de caracteres "[#j]"
 * y resetea el color. (Si j=3 -> imprime "[#3]" en color (3)"BLUE")
 */
void imprimir_jugador(int j) {
    printf_color(j);
    printf("[#%d]", j);
    printf_reset_color();
}

/*
 * void imprimir_contadores(t_jugadores js);
 * Se escribe el numero de OSOs que ha conseguido cada jugador.
 */
void imprimir_contadores(t_jugadores js) {
    int i;

    printf("OSOs:  ");
    for (i = 0; i < js.num_jugadores; i++) {
        imprimir_jugador(js.turno);
        printf(": %d | ", js.j[i].num_osos);
    }
    printf("\n");
}

