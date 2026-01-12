#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/validaciones.h"

// 1. Herramienta para pedir texto limpio (evita bugs de buffer)
void get_clean_input(char *buffer, int size, const char *prompt) {
	printf(" [>] %s", prompt);
	fflush(stdout); 
	fgets(buffer, size, stdin);
	
	size_t len = strlen(buffer);
	if (len > 0 && buffer[len - 1] == '\n') {
		buffer[len - 1] = '\0';
	}
}

// 2. Herramienta para pedir numeros seguros (sin que se cuelgue con letras)
int get_safe_int(const char *msg) {
	char temp_buff[64];
	get_clean_input(temp_buff, 64, msg);
	
	// Verificamos si es numerico
	for(int i = 0; temp_buff[i] != '\0'; i++) {
		if(!isdigit(temp_buff[i])) return -1; // Retorna -1 si hay letras
	}
	// Evitar convertir cadena vacia
	if(strlen(temp_buff) == 0) return 0;
	
	return atoi(temp_buff);
}

// 3. Algoritmo Modulo 10 (Validacion de Cedula Real)
int verify_ecuador_id(const char *id_code) {
	if (strlen(id_code) != 10) return 0;
	
	int total_accum = 0;
	int province_code = (id_code[0] - '0') * 10 + (id_code[1] - '0');
	
	if (province_code < 1 || province_code > 24) return 0;
	
	int factors[] = {2, 1, 2, 1, 2, 1, 2, 1, 2};
	for (int k = 0; k < 9; k++) {
		int current_digit = id_code[k] - '0';
		int product = current_digit * factors[k];
		
		if (product >= 10) product -= 9;
		total_accum += product;
	}
	
	int check_digit = id_code[9] - '0';
	int upper_ten = ((total_accum / 10) + 1) * 10;
	if (total_accum % 10 == 0) upper_ten = total_accum;
	
	return ((upper_ten - total_accum) == check_digit);
}
