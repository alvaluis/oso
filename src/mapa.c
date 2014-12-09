#include <stdio.h>
#include "colores.h"
#include "mapa.h"
#include "input.h"

void inicializar_casillas(t_mapa *mapa) {
    int f, c;

    mapa->num_casillas = mapa->num_filas * mapa->num_cols;
    mapa->num_casillas_en_blanco = mapa->num_filas * mapa->num_cols;

    for (f = 0; f < mapa->num_filas; f++)
    for (c = 0; c < mapa->num_cols; c++)
        mapa->c[f][c].letra = CASILLA_VACIA;
}

void inicializar_mapa(t_mapa *mapa) {
    printf("Mapa:\n");
    mapa->num_filas = pedir_entero("\t", "Filas", MIN_FILAS, MAX_FILAS);
    mapa->num_cols = pedir_entero("\t", "Columnas", MIN_COLS, MAX_COLS);
    inicializar_casillas(mapa);
}

void imprimir_mapa(t_mapa mapa) {
    int i, j;
    t_casilla casilla;

    printf("  |");
    for (i = 0; i < mapa.num_cols; i++)
        printf("%d|", i / 10);
    printf("\n");

    printf("  |");
    for (i = 0; i < mapa.num_cols; i++)
        printf("%d|", i % 10);
    printf("\n");

    for (i = 0; i < mapa.num_filas; i++) {
        printf("%02d|", i);
        for (j = 0; j < mapa.num_cols; j++) {
            casilla = mapa.c[i][j];
            if (casilla.letra != CASILLA_VACIA)
                printf_color(casilla.jugador);
            printf("%c\033[m|", casilla.letra);
        }
        printf("\n");
    }
    printf("\n");
}

void escribir_jugada(t_mapa *mapa, int j, int f, int c, char car) {
    mapa->c[f][c].jugador = j;
    mapa->c[f][c].letra = car;
    mapa->num_casillas_en_blanco--;
}

int calcular_osos(t_mapa *mapa, int f, int c, char car) {
    int osos = 0;

    if (car == 'S') {
        if (hay_un_oso(mapa, c, f, -1,  0, car)) osos++;
        if (hay_un_oso(mapa, c, f, -1, -1, car)) osos++;
        if (hay_un_oso(mapa, c, f,  0, -1, car)) osos++;
        if (hay_un_oso(mapa, c, f, +1, -1, car)) osos++;
    } else if (car == 'O') {
        if (hay_un_oso(mapa, c, f, -1,  0, car)) osos++;
        if (hay_un_oso(mapa, c, f, -1, -1, car)) osos++;
        if (hay_un_oso(mapa, c, f,  0, -1, car)) osos++;
        if (hay_un_oso(mapa, c, f, +1, -1, car)) osos++;
        if (hay_un_oso(mapa, c, f, +1,  0, car)) osos++;
        if (hay_un_oso(mapa, c, f, +1, +1, car)) osos++;
        if (hay_un_oso(mapa, c, f,  0, +1, car)) osos++;
        if (hay_un_oso(mapa, c, f, -1, +1, car)) osos++;
    }
    return osos;
}

int hay_un_oso(t_mapa *mapa, int c, int f, int dc, int df, char car) {
    int w = mapa->num_cols, h = mapa->num_filas;

    if (car == 'S') {
        if (c+dc >= 0 && c+dc < w && f+df >= 0 && f+df < h &&
            c-dc >= 0 && c-dc < w && f-df >= 0 && f-df < h &&
            mapa->c[f+df][c+dc].letra == 'O' && mapa->c[f-df][c-dc].letra == 'O')
            return 1;
        else
            return 0;
    }
    else if (car == 'O') {
        if (c+2*dc >= 0 && c+2*dc < w && f+2*df >= 0 && f+2*df < h &&
            mapa->c[f+df][c+dc].letra == 'S' && mapa->c[f+2*df][c+2*dc].letra == 'O')
            return 1;
        else
            return 0;
    }

    return 0;
}

