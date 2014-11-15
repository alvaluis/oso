#include <stdio.h>
#include <ctype.h>
#include "azar.h"
#include "duerme.h"
#include "mapa.h"
#include "jugadores.h"
#include "intel.h"
#include "input.h"

/*
 * Dado un mapa, un numero de jugador;
 * pide fila, columna y un caracter 'O' o 'S' a un jugador humano,
 * verifica fila,col,car y realiza la jugada.
 * Devuelve el numero de OSOs conseguidos con esa jugada.
 */
int jugar_humano(t_mapa *mapa, int j) {
    int f, c, r;
    char car;

    while (1) {
        printf(" Fila,Columna: ");
        r = scanf("%d,%d", &f,&c);
        descartar_linea();

        if ((r == 2)&&
            (f >= 0 && f < mapa->num_filas)&&
            (c >= 0 && c < mapa->num_cols)&&
            (mapa->c[f][c].letra == CASILLA_VACIA))
            break;
    }

    while (1) {
        printf("Letra [O/S]: ");
        scanf("%c", &car);
        descartar_linea();

        car = toupper(car);
        if (car == 'O' || car == 'S') break;
    }

    escribir_jugada(mapa, j, f, c, car);
    return calcular_osos(mapa, f, c, car);
}

/*
 * Dado un mapa y numero de jugador; el programa decide una jugada.
 * Tiene que ser una jugada reglamentaria.
 * Y, estaria bien si la jugada fuera mas o menos inteligente.
 * Realiza la jugada seleccionada y duerme un rato.
 * Devuelve el numero de OSOs conseguidos con esa jugada.
 */
int jugar_maquina(t_mapa *mapa, int j) {
    t_jugada jugada;

    determinar_jugada(mapa, NULL, &jugada); //FIXME
    escribir_jugada(mapa, j, jugada.f, jugada.c, jugada.car);
    //duerme_un_rato(); //FIXME
    return calcular_osos(mapa, jugada.f, jugada.c, jugada.car);
}

/*
 * Dado un mapa y jugadores,
 * si el contador de casillas en blanco esta a cero mira que jugador/es
 * ha/n conseguido mas OSOs y los imprime por pantalla.
 * Devuelve cierto si el juego se ha acabado. Y sino, falso.
 */
int se_acabo_el_juego(t_mapa mapa, t_jugadores js) {
    int i, max = 0;
    if (mapa.num_casillas_en_blanco > 0) return 0;

    printf("JUGADOR/ES GANADOR/ES:");
    for (i = 0; i < js.num_jugadores; i++) {
        if (js.j[i].num_osos > max)
            max = js.j[i].num_osos;
    }
    for (i = 0; i < js.num_jugadores; i++) {
        if (js.j[i].num_osos == max)
            imprimir_jugador(i);
    }
    printf("!\n");
    return 1;
}

/*
 * Imprime el mapa y los contadores de OSOs de cada jugador.
 */
void imprimir_estado_juego(t_mapa mapa, t_jugadores js) {
    printf("\n");
    imprimir_mapa(mapa);
    imprimir_contadores(js);
}

/*
 * Dado un mapa y jugadores,
 * - Se imprime el jugador que tiene el turno, se mira si es humano o maquina
 * y se le hace jugar. Se le añaden a su total de OSOs los obtenidos con la
 * jugada. Se imprime por pantalla los OSOs obtenidos con la jugada.
 * - Si no obtuvo ninguno pasa el turno.
 */
void realizar_jugada(t_mapa *mapa, t_jugadores *js) {
    int osos;

    printf("Jugador ");
    imprimir_jugador(js->turno);
    if (js->j[js->turno].tipo == JUGADOR_HUMANO)
        osos = jugar_humano(mapa,js->turno);
    else
        osos = jugar_maquina(mapa,js->turno);

    js->j[js->turno].num_osos += osos;
    printf(" %d osos\n", osos);
    if (osos == 0) pasar_turno(js);
}

/*
 * Inicializa la generación de números aleatorios, jugadores y mapa.
 * Imprime el estado del juego.
 * Mientras no se haya acabado el juego:
 * - Llama a realizar_jugada() que es la función que hace que el humano
 *   o la maquina que tiene el turno realize una jugada.
 * - Imprime el estado del juego.
 */

int main() {
    t_jugadores js;
    t_mapa mapa;

    inicializar_azar();
    inicializar_jugadores(&js);
    inicializar_mapa(&mapa);

    while (1) {
        imprimir_estado_juego(mapa, js);
        if (se_acabo_el_juego(mapa, js)) break;
        realizar_jugada(&mapa, &js);
    }
    return 0;
}

