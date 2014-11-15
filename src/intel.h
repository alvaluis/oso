#ifndef INTEL_H
#define INTEL_H

#include "mapa.h"
#include "jugadores.h"

typedef struct {
    int f;
    int c;
    char car;
} t_jugada;

void determinar_jugada(t_mapa *mapa, t_jugadores *jugadores, t_jugada *jugada);
void jugadas_validas(t_mapa *mapa, t_jugada *jugadas, int *num_jugadas);
float calcular_score(t_mapa *mapa, t_jugadores *jugadores, t_jugada *jugada);

#endif /* INTEL_H */

