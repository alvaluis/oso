# OSO

Implementación sencilla del [juego del OSO](https://es.wikipedia.org/wiki/Oso_%28juego%29).

Cuando un jugador recibe el turno debe poner la letra `S` o la letra `O` en una casilla vacía del tablero. Si al hacerlo construye la secuencia `O-S-O` en horizontal, vertical o diagonal, conserva el turno. El objetivo del juego es construir el mayor número de OSOs posibles.

## Compilación

El juego se construye usando [CMake](http://cmake.org). Primero, se configura:

    $ cmake .

Y luego, se compila:

    $ make

Una vez hecho esto, se puede ejecutar el juego con `./juego`.
