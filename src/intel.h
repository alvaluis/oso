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

void determinar_jugada(t_mapa *mapa, t_jugadores *jugadores, t_jugada *jugada);
void jugadas_validas(t_mapa *mapa, t_lista_jugadas *dst);
void filtrar_maximo_score(t_mapa *mapa, t_jugadores *jugadores, t_lista_jugadas *src, t_lista_jugadas *dst);
float calcular_score(t_mapa *mapa, t_jugadores *jugadores, t_jugada *jugada);

#endif /* INTEL_H */

