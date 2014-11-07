#include <stdio.h>
#include "colores.h"
#include "mapa.h"
#include "input.h"

/*
 * void inicializar_casillas(t_mapa *mapa);
 * Dado un puntero a mapa con los campos filas y columnas inicializados,
 * se inicializa todas sus casillas a CASILLA_VACIA y NINGUN_JUGADOR.
 * Tambien se inicializan num_casillas y num_casillas_en_blanco.
 */
void inicializar_casillas(t_mapa *mapa) {
    int i, j;

    mapa->num_casillas = mapa->num_filas * mapa->num_cols;
    mapa->num_casillas_en_blanco = mapa->num_filas * mapa->num_cols;

    for (i = 0; i <= mapa->num_filas; i++) {
        for (j = 0; j <= mapa->num_cols; j++) {
            mapa->c[i][j].letra = CASILLA_VACIA;
            mapa->c[i][j].jugador = NINGUN_JUGADOR;
        }
    }
}

/*
 * void inicializar_mapa(t_mapa *mapa);
 * Dado un puntero a mapa, se preguntan filas y columnas, se verifica que esten
 * entre sus minimos y maximos correspondientes.
 * Se asignan a mapa y se llama a inicializar casillas.
 */
void inicializar_mapa(t_mapa *mapa) {
    printf("Mapa:\n");
    mapa->num_filas = pedir_entero("Filas", 3, 15);
    mapa->num_cols = pedir_entero("Columnas", 3, 35);
    inicializar_casillas(mapa);
}

/*
 * void imprimir_mapa(t_mapa mapa);
 * Dado un mapa imprime el mapa de tal forma que las 'O's y 'S's
 * se imprimen con el color del jugador que las hizo.
 */
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
            printf_color(casilla.jugador);
            printf("%c\033[m|", casilla.letra);
        }
        printf("\n");
    }
    printf("\n");
}

/*
 * Dado un mapa, un numero de jugador, fila, columna y un caracter 'O' o 'S';
 * escribe el car en fila,col del mapa para el jugador en turno
 * y decrementa el contador de casillas en blanco del mapa.
 */
void escribir_jugada(t_mapa *mapa, int j, int f, int c, char car) {
    /* COMPLETAR */
}

/*
 * int calcular_osos(t_mapa *mapa, int f, int c, char car);
 * Dado un mapa, fila "f", columna "c" y un caracter "car" = 'O' o 'S';
 * devuelve cuantos OSOs se crearian al escribir el car en fila,columna.
 */
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

/**
 * Comprueba si se crearía un OSO, en la dirección marcada por dc y df, al poner
 * el caracter car en la casilla (c,f).
 * @param mapa el mapa
 * @param c la columna de la casilla donde se pone car
 * @param f la fila de la casilla donde se pone car
 * @param dc dirección horizontal en la que miramos si hay un OSO
 * @param df dirección vertical en la que miramos si hay un OSO
 * @param car la letra que pondríamos en la casilla
 * @return 1 si se crea OSO, 0 en cualquier otro caso
 **/
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

