#ifndef VALIDACIONES_H
#define VALIDACIONES_H

// Prototipos (La lista de herramientas disponibles)
void get_clean_input(char *buffer, int size, const char *prompt);
int get_safe_int(const char *msg);
int verify_ecuador_id(const char *id_code);

#endif
