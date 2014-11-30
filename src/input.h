#ifndef INPUT_H
#define INPUT_H

/*
 * void descartar_linea();
 * Lee y descarta la entrada del usuario hasta encontrarse
 * con un '\n', que tambien es descartado.
 */
void descartar_linea();

/*
 * int pedir_entero(const char *prefijo, const char *nombre, int min, int max);
 * Pide un entero al usuario, hasta que este introduce
 * un valor válido (entre min y max).
 */
int pedir_entero(const char *prefijo, const char *nombre, int min, int max);

/*
 * void inicializar_tty();
 * Obtiene información del estado actual del pseudo-terminal,
 * necesaria para el correcto funcionamiento de las demás funciones.
 * Se asegura que el pseudo-terminal se restablece al salir.
 * Debe llamarse una única vez.
 */
void inicializar_tty();

/*
 * void adquirir_tty();
 * Ajusta el pseudo-terminal para aplicaciones interactivas;
 * los caracteres se pasan immediatamente al programa y no
 * se ven en el terminal.
 */
void adquirir_tty();

/*
 * void restablecer_tty();
 * Restablece el terminal a su estado inicial.
 */
void restablecer_tty();

#endif /* INPUT_H */

