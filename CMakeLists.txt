cmake_minimum_required (VERSION 2.6)
project (OSO)

add_definitions (-Wall -Wextra -Wno-unused-parameter)

add_executable (
  juego src/juego.c

  src/azar.c
  src/colores.c
  src/duerme.c
  src/input.c
  src/jugadores.c
  src/mapa.c
)
