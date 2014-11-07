#include <stdio.h>
#include "colores.h"
#include "jugadores.h"



/*
 * void inicializar_jugadores(t_jugadores *js);
 * Dado un puntero a jugadores los inicializa pidiendo al usuario el numero
 * de jugadores y el de jugadores humanos, assegurandose que ambos estan
 * entre el numero de jugadores minimo y maximo permitidos.
 * E inicializa el turno al primer jugador.
 */
void inicializar_jugadores(t_jugadores *js) {
	int i;	
	printf("Numero total de jugadores (2-6): ");
	scanf("%d", &(*js).num_jugadores);	
	if((*js).num_jugadores >= MIN_JUGADORES && (*js).num_jugadores <= MAX_JUGADORES)
	{
		printf("Numero de jugadores humanos (0-%d): ", (*js).num_jugadores);  
		scanf("%d",&(*js).num_humanos);
		if((*js).num_humanos >= MIN_HUMANOS && (*js).num_humanos <= (*js).num_jugadores)
		{
			(*js).turno = 0;		
			for(i = 0; i < (*js).num_jugadores; i++)			
				(*js).j[i].num_osos = 0; 	
			for (i = 0; i < (*js).num_humanos; i++)
				(*js).j[i].tipo = JUGADOR_HUMANO;
			for(i = (*js).num_humanos; i < (*js).num_jugadores; i++)
				(*js).j[i].tipo = JUGADOR_MAQUINA;
		}
	}
}

/*
 * void pasar_turno(t_jugadores *js);
 * Dado un puntero a jugadores pasa el turno al siguiente jugador
 */
void pasar_turno(t_jugadores *js) {
  /* COMPLETAR */
}

/*
 * Dado un entero 'j' (correspondiente al jugador numero 'j',
 * imprime en el color 'j' la cadena de caracteres "[#j]"
 * y resetea el color. (Si j=3 -> imprime "[#3]" en color (3)"BLUE")
 */
void imprimir_jugador(int j) {
  /* COMPLETAR */
}

/*
 * void imprimir_contadores(t_jugadores js);
 * Se escribe el numero de OSOs que ha conseguido cada jugador.
 */
void imprimir_contadores(t_jugadores js) {
  /* COMPLETAR */
}

