# OSO

Implementación sencilla del [juego del OSO](https://es.wikipedia.org/wiki/Oso_%28juego%29).

Cuando un jugador recibe el turno debe poner la letra `S` o la letra `O` en una casilla vacía del tablero. Si al hacerlo construye la secuencia `O-S-O` en horizontal, vertical o diagonal, conserva el turno. El objetivo del juego es construir el mayor número de OSOs posibles. El juego termina cuando no quedan casillas vacías en el tablero.

## Compilación

El juego se construye usando [CMake](http://cmake.org). Primero, se configura:

    $ cmake .

Y luego, se compila:

    $ make

Una vez hecho esto, se puede ejecutar el juego con `./juego`.

## Mejoras

Lista de mejoras respecto del juego original:

 - En el momento de introducir fila y columna, pueden usarse las flechas para escoger la casilla.
   Cuando se tiene el cursor sobre la casilla, presionar immediatamente la letra y se hace la jugada.
 - La entrada de datos no tolera letras ni entra en bucle infinito.
 - La entrada de datos ignora (descarta) parametros sobrantes al final de la línea.
 - Prescindir de la constante `NINGUN_JUGADOR`.
 - Mejoras en Inteligencia Artificial.
 - La inteligencia artificial acepta puntero a `t_jugadores`, para tener más información del contexto.
 - El azar se inicializa de forma más precisa, para que varie con más frecuencia.

La intención es que estas mejoras pasen desapercibidas, de manera que a primera vista el juego se comporta como el original.
La mayoría de ellas son a nivel de estructura del código, pero tambien hay algunas que añaden características al juego.
