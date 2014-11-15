#include <stdio.h>
#include "intel.h"
#include "azar.h"

void jugadas_validas(t_mapa *mapa, t_lista_jugadas *dst) {
    int f, c;
    dst->num = 0;

    for (f = 0; f < mapa->num_filas; f++)
    for (c = 0; c < mapa->num_cols; c++)
        if (mapa->c[f][c].letra == CASILLA_VACIA) {
            /* Añadir jugada O */
            dst->jugadas[dst->num].f = f;
            dst->jugadas[dst->num].c = c;
            dst->jugadas[dst->num].car = 'O';
            dst->num++;

            /* Añadir jugada S */
            dst->jugadas[dst->num].f = f;
            dst->jugadas[dst->num].c = c;
            dst->jugadas[dst->num].car = 'S';
            dst->num++;
        }
}

void determinar_jugada(t_mapa *mapa, t_jugadores *jugadores, t_jugada *jugada) {
    t_lista_jugadas lista1, lista2;

    /* Enumerar posibles jugadas */
    jugadas_validas(mapa, &lista1);

    /* Filtar las de máximo score */
    filtrar_maximo_score(mapa, jugadores, &lista1, &lista2);

    /* Filtros adicionales */
    //TODO (cantonades i evitar posar O's)

    /* De todas las filtradas, retornar una jugada aleatoria */
    *jugada = lista2.jugadas[indice_al_azar(lista2.num)];
}

void filtrar_maximo_score(t_mapa *mapa, t_jugadores *jugadores, t_lista_jugadas *src, t_lista_jugadas *dst) {
    float max_score = -999, score;
    int i;

    for (i = 0; i < src->num; i++) {
        score = calcular_score(mapa, jugadores, &src->jugadas[i]);

        /* Si tiene menos score que las anteriores, ignorar */
        if (score < max_score) continue;

        /* Si supera todas las anteriores, limpiar la lista */
        if (score > max_score) {
            dst->num = 0;
            max_score = score;
        }

        /* Añadir la jugada a la lista */
        dst->jugadas[dst->num] = src->jugadas[i];
        dst->num++;
    }
}

float calcular_score(t_mapa *mapa, t_jugadores *jugadores, t_jugada *jugada) {
    return calcular_osos(mapa, jugada->f, jugada->c, jugada->car);
}

