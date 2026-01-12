#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/auth.h"
#include "../include/validaciones.h"

// --- BASE DE DATOS TEMPORAL DE USUARIOS (HARDCODED) ---
// En el futuro (Semana 7) esto se leera de un archivo encriptado.
UserCredential temp_users[] = {
	{"admin", "1234", ROLE_ADMIN},        // Administrador
{"DOC01", "med123", ROLE_DOCTOR},     // Un medico (usa su codigo)
	{"1710034065", "pac123", ROLE_PATIENT} // Un paciente (usa su cedula)
};
int total_temp_users = 3;

// Utilidad visual interna para el encabezado
void draw_auth_header() {
	system("cls");
	printf("\n *************************************************\n");
	printf("   SISTEMA MEDICO - ACCESO SEGURO\n");
	printf(" *************************************************\n");
}

int core_perform_login(char *logged_user_id_out) {
	char input_user[20];
	char input_pass[20];
	int attempts = 0;
	int logged_role = ROLE_NONE;
	
	while (attempts < 3 && logged_role == ROLE_NONE) {
		draw_auth_header();
		if (attempts > 0) {
			printf(" [!] Intento %d/3 fallido. Credenciales incorrectas.\n", attempts);
			printf(" -------------------------------------------------\n");
		}
		
		get_clean_input(input_user, 20, "Usuario/ID: ");
		get_clean_input(input_pass, 20, "Contrasena: "); // NOTA: En consola real no se oculta facil
		
		// Verificacion contra la base temporal
		for (int i = 0; i < total_temp_users; i++) {
			if (strcmp(input_user, temp_users[i].username) == 0 &&
				strcmp(input_pass, temp_users[i].password) == 0) {
				
				logged_role = temp_users[i].role_id;
				strcpy(logged_user_id_out, temp_users[i].username);
				printf("\n [OK] Acceso concedido. Bienvenido %s.\n", input_user);
				system("pause");
				return logged_role; // Login exitoso
			}
		}
		attempts++;
	}
	
	printf("\n [X] Error: Demasiados intentos fallidos. Sistema bloqueado.\n");
	system("pause");
	exit(0); // Cierra el programa por seguridad
	return ROLE_NONE;
}
