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

#endif /* INPUT_H */

