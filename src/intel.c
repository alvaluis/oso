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
    filtrar_adicional(mapa, &lista2, &lista1);

    /* De todas las filtradas, retornar una jugada aleatoria */
    if (lista1.num == 0)
        *jugada = lista2.jugadas[indice_al_azar(lista2.num)];
    else
        *jugada = lista1.jugadas[indice_al_azar(lista1.num)]; //FIXME
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
    int f,c, max_osos = 0;
    t_mapa mapa2;
    int osos = calcular_osos(mapa, jugada->f, jugada->c, jugada->car);
    if (osos > 0) return osos;
    
    mapa2 = *mapa;
    escribir_jugada(&mapa2, jugadores->turno, jugada->f, jugada->c, jugada->car);
    for (f = 0; f < mapa->num_filas; f++)
    for (c = 0; c < mapa->num_cols; c++)
        if (mapa->c[f][c].letra == CASILLA_VACIA) {
            osos = calcular_osos(&mapa2, f, c, 'O');
            if (osos > max_osos) max_osos = osos;
            
            osos = calcular_osos(&mapa2, f, c, 'S');
            if (osos > max_osos) max_osos = osos;
        }
    
    return -max_osos;
}

void filtrar_adicional(t_mapa *mapa, t_lista_jugadas *src, t_lista_jugadas *dst) {
    int i;
    t_jugada *jugada;
    dst->num = 0;
    
    for (i = 0; i < src->num; i++){
        jugada = &src->jugadas[i];
        if (jugada->car == 'O') continue;
        if (jugada->f == 0 || jugada->f == MAX_FILAS-1 || jugada->c == 0 || jugada->c == MAX_COLS-1) continue;
        dst->jugadas[dst->num] = *jugada;
        dst->num ++;
    }
}
