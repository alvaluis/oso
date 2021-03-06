#ifndef JUGADORES_H
#define JUGADORES_H

#define MIN_JUGADORES	2
#define MAX_JUGADORES	6
#define MIN_HUMANOS	0

typedef enum {
    JUGADOR_MAQUINA,
    JUGADOR_HUMANO
} t_jugador_tipo;

typedef struct {
    int num_osos;
    t_jugador_tipo tipo;
} t_jugador;

typedef struct {
    int num_jugadores;
    int num_humanos;
    int turno; // Jugador que tiene el turno.
    t_jugador j[MAX_JUGADORES];
    /* En las primeras 'num_humanos' posiciones de 'j' estan los jugadores
       de tipo humano y a continuación los de tipo máquina. */
} t_jugadores;

/*
 * void inicializar_jugadores(t_jugadores *js);
 * Dado un puntero a jugadores los inicializa pidiendo al usuario el número
 * de jugadores y el de jugadores humanos, assegurandose que ambos estan
 * entre el número de jugadores mínimo y máximo permitidos.
 * Tambien inicializa el turno al primer jugador.
 */
void inicializar_jugadores(t_jugadores *js);

/*
 * void pasar_turno(t_jugadores *js);
 * Dado un puntero a jugadores pasa el turno al siguiente jugador.
 */
void pasar_turno(t_jugadores *js);

/*
 * void imprimir_jugador(int j);
 * Dado un entero 'j' (correspondiente al jugador numero 'j',
 * imprime en el color 'j' la cadena de caracteres "[#j]"
 * y resetea el color. (Si j=3 -> imprime "[#3]" en color (3)"BLUE")
 */
void imprimir_jugador(int j);

/*
 * void imprimir_contadores(t_jugadores js);
 * Se escribe el numero de OSOs que ha conseguido cada jugador.
 */
void imprimir_contadores(t_jugadores js);

#endif /* JUGADORES_H */

