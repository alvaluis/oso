#ifndef INTEL_H
#define INTEL_H

#include "mapa.h"
#include "jugadores.h"

typedef struct {
    int f;
    int c;
    char car;
} t_jugada;

typedef struct {
    t_jugada jugadas[MAX_FILAS * MAX_COLS * 2];
    int num;
} t_lista_jugadas;

/*
 * void jugadas_validas(t_mapa *mapa, t_lista_jugadas *dst);
 * Dado un mapa, llena dst con todas las jugadas legales que se
 * podrían efectuar en dicho mapa.
 */
void jugadas_validas(t_mapa *mapa, t_lista_jugadas *dst);

/*
 * void determinar_jugada(t_mapa *mapa, t_jugadores *jugadores, t_jugada *jugada);
 * Método principal de la IA. Dado mapa y jugadores, escoge
 * una jugada a realizar por la máquina.
 *
 * Precondición: existe por lo menos una jugada válida.
 */
void determinar_jugada(t_mapa *mapa, t_jugadores *jugadores, t_jugada *jugada);

/*
 * void filtrar_maximo_score(t_mapa *mapa, t_jugadores *jugadores, t_lista_jugadas *src, t_lista_jugadas *dst);
 * Calcula la puntuación (score) de cada jugada en src
 * y deja la(s) jugadas con mayor score en dst.
 *
 * Precondición: existe por lo menos una jugada en src.
 */
void filtrar_maximo_score(t_mapa *mapa, t_jugadores *jugadores, t_lista_jugadas *src, t_lista_jugadas *dst);

/*
 * float calcular_score(t_mapa *mapa, t_jugadores *jugadores, t_jugada *jugada);
 * Dado mapa y jugadores, calcula la puntuación (score) que tendría la
 * jugada si se hiciera por el jugador que tiene el turno.
 */
float calcular_score(t_mapa *mapa, t_jugadores *jugadores, t_jugada *jugada);

void filtrar_adicional(t_mapa *mapa, t_lista_jugadas *src, t_lista_jugadas *dst);

#endif /* INTEL_H */

