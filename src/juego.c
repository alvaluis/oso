#include <stdio.h>
#include <ctype.h>
#include "azar.h"
#include "duerme.h"
#include "mapa.h"
#include "jugadores.h"
#include "intel.h"
#include "input.h"

#define ESTADO_INTRODUCIR  1
#define ESTADO_SELECCIONAR 2
#define CAMPO_POSICION 1
#define CAMPO_LETRA    2
#define CAMPO_NINGUNO  3
#define MAXIMO_ENTRADA 10

/*
 * En el momento de pedir columna, imprime la posición (f,c)
 * como si la hubiera escrito el usuario y situa el cursor
 * en la posición indicada del mapa impreso anteriormente.
 */
static void situar_cursor(t_mapa *mapa, int f, int c) {
    /* Ir a la posición guardada y limpiar lo que hay "introducido" */
    printf("\e[u\e[K");
    /* Imprimir la posición */
    printf("%2d, %2d", f, c);
    /* Situarse en la casilla de la esquina inferior izquierda */
    printf("\e[3F");
    /* Subir hasta la fila correspondiente */
    if (f < mapa->num_filas-1)
        printf("\e[%dF", (mapa->num_filas-1) - f);
    /* Avanzar hasta la columna correspondiente */
    printf("\e[%dG", 4 + c * 2);
}

/*
 * Dado un mapa, un numero de jugador;
 * Pide fila, columna y un carácter 'O' o 'S' a un jugador humano,
 * verifica que sean válidos y realiza la jugada.
 * Devuelve el numero de OSOs conseguidos con esa jugada.
 *
 * ## Método de entrada
 *
 * Hay dos estados, "introducir" y "seleccionar".
 *
 *  - Introducir. El usuario debe teclear las coordenadas de la
 *    casilla, pulsar Enter, introducir la letra, y pulsar Enter.
 *    Este es el modo inicial.
 *
 *  - Seleccionar. El usuario usa las flechas del teclado para
 *    mover el cursor de la pantalla hasta situar este sobre
 *    la casilla que quiera. Con el cursor encima de una casilla
 *    vacía, presiona la letra que desea poner.
 *
 * Si el usuario está en modo introducir, al presionar cualquier
 * flecha se borrará lo que haya puesto y se pasará al modo
 * seleccionar, con el cursor en la casilla del medio del tablero.
 *
 * Si el usuario está en modo seleccionar, al presionar Suprimir
 * o Backspace se le devolverá al modo Introducir de nuevo.
 */
int jugar_humano(t_mapa *mapa, int j) {
    int f, c, r;
    char car, i;

    int valido;
    int estado = ESTADO_INTRODUCIR;
    int campo = CAMPO_POSICION;
    char entrada [MAXIMO_ENTRADA+1] = "";
    int entrada_l = 0;

    adquirir_tty();
    printf(" Fila,Columna: \e[s");

    while (campo != CAMPO_NINGUNO) {
        i = fgetc(stdin);
        if (estado == ESTADO_INTRODUCIR) {
            if (i == '\n') {

                /* ESTADO:   INTRODUCIR *
                 * CARÁCTER: NEWLINE    */
                entrada[entrada_l] = '\0';
                if (campo == CAMPO_POSICION) {
                    r = sscanf(entrada, "%d,%d", &f, &c);
                    valido = (r == 2)
                             && (f >= 0 && f < mapa->num_filas)
                             && (c >= 0 && c < mapa->num_cols)
                             && (mapa->c[f][c].letra == CASILLA_VACIA);
                } else {
                    r = sscanf(entrada, "%c", &car);
                    car = toupper(car);
                    valido = (r == 1) && (car == 'S' || car == 'O');
                }

                if (valido) {
                    entrada_l = 0;
                    printf("\r\n");
                    campo++;
                    if (campo == CAMPO_LETRA)
                        printf("Letra [O/S]: ");
                } else {
                    while (entrada_l > 0) {
                        printf("\e[D");
                        entrada_l--;
                    }
                    printf("\e[K");
                }

            } else if (i == '\e') {

                /* ESTADO:   INTRODUCIR *
                 * CARÁCTER: ESCAPE     */
                if (fgetc(stdin) == '[') {
                    i = fgetc(stdin);
                    if (i >= 'A' && i <= 'D') {
                        f = mapa->num_filas / 2;
                        c = mapa->num_cols / 2;
                        situar_cursor(mapa, f, c);
                        estado = ESTADO_SELECCIONAR;
                    }
                }

            } else if (i == 0x7F || i == '\b') {

                /* ESTADO:   INTRODUCIR      *
                 * CARÁCTER: DEL / BACKSPACE */
                if (entrada_l > 0) {
                    entrada_l--;
                    printf("\e[D\e[K");
                }

            } else if (isprint(i)) {

                /* ESTADO:   INTRODUCIR *
                 * CARÁCTER: IMPRIMIBLE */
                if (entrada_l < MAXIMO_ENTRADA) {
                    entrada[entrada_l++] = i;
                    printf("%c", i);
                }

            }
        } else {
            if (isspace(i)) {

                /* ESTADO:   SELECCIONAR *
                 * CARÁCTER: ESPACIADO   */
                if (mapa->c[f][c].letra == CASILLA_VACIA) {
                    printf("\e[u\e[K%2d, %2d\r\nLetra [O/S]: ", f, c);
                    entrada_l = 0;
                    estado = ESTADO_INTRODUCIR;
                    campo = CAMPO_LETRA;
                }

            } else if (i == '\e') {

                /* ESTADO:   SELECCIONAR *
                 * CARÁCTER: ESCAPE      */
                if (fgetc(stdin) == '[') {
                    i = fgetc(stdin);
                    if (i == 'A') {
                        if (f > 0) situar_cursor(mapa, --f, c);
                    } else if (i == 'D') {
                        if (c > 0) situar_cursor(mapa, f, --c);
                    } else if (i == 'B') {
                        if (f < mapa->num_filas-1) situar_cursor(mapa, ++f, c);
                    } else if (i == 'C') {
                        if (c < mapa->num_cols-1)  situar_cursor(mapa, f, ++c);
                    }
                }

            } else if (i == 0x7F || i == '\b') {

                /* ESTADO:   SELECCIONAR     *
                 * CARÁCTER: DEL / BACKSPACE */
                printf("\e[u\e[K");
                entrada_l = 0;
                estado = ESTADO_INTRODUCIR;
                campo = CAMPO_POSICION;

            } else if (isprint(i)) {

                /* ESTADO:   SELECCIONAR *
                 * CARÁCTER: IMPRIMIBLE  */
                i = toupper(i);
                if (mapa->c[f][c].letra == CASILLA_VACIA && (i == 'S' || i == 'O')) {
                    car = i;
                    printf("\e[u\e[K%2d, %2d\r\nLetra [O/S]: %c\r\n", f, c, car);
                    campo = CAMPO_NINGUNO;
                }

            }
        }
    }

    restablecer_tty();

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
int jugar_maquina(t_mapa *mapa, t_jugadores *js, int j) {
    t_jugada jugada;

    determinar_jugada(mapa, js, &jugada);
    escribir_jugada(mapa, j, jugada.f, jugada.c, jugada.car);
    duerme_un_rato();
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
        osos = jugar_humano(mapa, js->turno);
    else
        osos = jugar_maquina(mapa, js, js->turno);

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
    inicializar_tty();

    inicializar_jugadores(&js);
    inicializar_mapa(&mapa);

    while (1) {
        imprimir_estado_juego(mapa, js);
        if (se_acabo_el_juego(mapa, js)) break;
        realizar_jugada(&mapa, &js);
    }
    return 0;
}

