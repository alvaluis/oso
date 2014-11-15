#include <stdio.h>
#include "intel.h"
#include "mapa.h"
#include "azar.h"

void jugadas_validas(t_mapa *mapa, t_jugada *jugadas, int *num_jugadas) {
    int i = 0, f, c;
    for (f = 0; f < mapa->num_filas; f++)
    for (c = 0; c < mapa->num_cols; c++)
        if (mapa->c[f][c].letra == CASILLA_VACIA) {
            /* Añadir jugada O */
            jugadas[i].f = f;
            jugadas[i].c = c;
            jugadas[i].car = 'O';
            i++;

            /* Añadir jugada S */
            jugadas[i].f = f;
            jugadas[i].c = c;
            jugadas[i].car = 'S';
            i++;
        }
    *num_jugadas = i;
}

void determinar_jugada(t_mapa *mapa, t_jugadores *jugadores, t_jugada *jugada) {
    t_jugada jugadas1[MAX_FILAS*MAX_COLS*2];
    t_jugada jugadas2[MAX_FILAS*MAX_COLS*2];
    int num_jugadas, i1, i2 = 0;
    float score, max_score = -10;

    jugadas_validas(mapa, jugadas1, &num_jugadas);
    for (i1 = 0; i1 < num_jugadas; i1++) {
        score = calcular_score(mapa, jugadores, &jugadas1[i1]);
        if (score >= max_score) {
            if(score > max_score) {
                i2 = 0;
                max_score = score;
            }
            jugadas2[i2] = jugadas1[i1];
            i2++;
        }
    }
    //TODO (cantonades i evitar posar O's)
    *jugada = jugadas2[indice_al_azar(i2)];
}

float calcular_score(t_mapa *mapa, t_jugadores *jugadores, t_jugada *jugada) {
    return calcular_osos(mapa, jugada->f, jugada->c, jugada->car);
}

