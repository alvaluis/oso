#ifndef MAPA_H
#define MAPA_H

#define MIN_FILAS	 3
#define MIN_COLS	 3
#define MAX_FILAS	15
#define MAX_COLS	35

#define NINGUN_JUGADOR	-1
// No puede ser 0 porque se pensaria que esta escrita por el jugador 0 FIXME
#define CASILLA_VACIA	' '

typedef struct {
    char letra;
    int jugador;
} t_casilla;

typedef struct {
    int num_filas;
    int num_cols;
    int num_casillas;
    int num_casillas_en_blanco;
    t_casilla c[MAX_FILAS][MAX_COLS];
} t_mapa;


/*
 * void inicializar_casillas(t_mapa *mapa);
 * Dado un puntero a mapa con los campos filas y columnas inicializados,
 * se inicializa todas sus casillas a CASILLA_VACIA y NINGUN_JUGADOR.
 * Tambien se inicializan num_casillas y num_casillas_en_blanco.
 */
void inicializar_casillas(t_mapa *mapa);

/*
 * void inicializar_mapa(t_mapa *mapa);
 * Dado un puntero a mapa, se preguntan filas y columnas, se verifica que esten
 * entre sus minimos y maximos correspondientes.
 * Se asignan a mapa y se llama a inicializar casillas.
 */
void inicializar_mapa(t_mapa *mapa);

/*
 * void imprimir_mapa(t_mapa mapa);
 * Dado un mapa imprime el mapa de tal forma que las 'O's y 'S's
 * se imprimen con el color del jugador que las hizo.
 */
void imprimir_mapa(t_mapa mapa);

/*
 * void escribir_jugada(t_mapa *mapa, int j, int f, int c, char car);
 * Dado un mapa, un numero de jugador, fila, columna y un caracter 'O' o 'S';
 * escribe el car en la casilla (c,f) del mapa para el jugador en turno
 * y decrementa el contador de casillas en blanco del mapa.
 *
 * Precondición: la casilla (c,f) está vacía.
 */
void escribir_jugada(t_mapa *mapa, int j, int f, int c, char car);

/*
 * int calcular_osos(t_mapa *mapa, int f, int c, char car);
 * Dado un mapa, fila "f", columna "c" y un caracter "car" = 'O' o 'S';
 * devuelve cuantos OSOs se crearian al escribir el car en fila,columna.
 */
int calcular_osos(t_mapa *mapa, int f, int c, char car);

/*
 * int hay_un_oso(t_mapa *mapa, int c, int f, int dc, int df, char car);
 * Comprueba si se crearía un OSO, en la dirección marcada por dc y df,
 * al poner el caracter car en la casilla (c,f).
 *
 * @param mapa el mapa
 * @param c la columna de la casilla donde se pone car
 * @param f la fila de la casilla donde se pone car
 * @param dc dirección horizontal en la que miramos si hay un OSO
 * @param df dirección vertical en la que miramos si hay un OSO
 * @param car la letra que pondríamos en la casilla
 * @return 1 si se crea OSO, 0 en cualquier otro caso
 */
int hay_un_oso(t_mapa *mapa, int c, int f, int dc, int df, char car);

#endif /* MAPA_H */

