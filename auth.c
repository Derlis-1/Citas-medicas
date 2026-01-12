#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/auth.h"
#include "../include/validaciones.h"

// Base de datos temporal
UserCredential temp_users[100] = {
	{"admin", "1234", ROLE_ADMIN},
{"DOC01", "med123", ROLE_DOCTOR},
	{"1710034065", "pac123", ROLE_PATIENT}
};
int total_users_auth = 3;

void draw_auth_header(const char *subtitle) {
	system("cls");
	printf("\n *************************************************\n");
	printf("   SISTEMA DE SALUD - ACCESO SEGURO\n");
	printf("   %s\n", subtitle);
	printf(" *************************************************\n");
}

// --- REGISTRO BLINDADO (SOLUCION FINAL) ---
void sub_handle_register() {
	if (total_users_auth >= 100) {
		printf(" [!] Base de datos llena.\n"); return;
	}
	
	char raw_opt[10]; // Buffer para leer la opcion como texto
	int final_role = ROLE_PATIENT;
	int valid_selection = 0;
	
	// Bucle: No te deja salir hasta que elijas 1, 2 o 3
	while (!valid_selection) {
		draw_auth_header("NUEVO REGISTRO DE USUARIO");
		printf("   Seleccione el tipo de cuenta:\n");
		printf("   1. Paciente\n");
		printf("   2. Medico / Especialista\n");
		printf("   3. Administrativo\n");
		printf(" --------------------------------\n");
		
		// LEEMOS COMO TEXTO (Esto evita el error de "ola")
		get_clean_input(raw_opt, 10, "Escriba 1, 2 o 3: ");
		
		// Verificamos solo el primer caracter
		if (raw_opt[0] == '1') { final_role = ROLE_PATIENT; valid_selection = 1; }
		else if (raw_opt[0] == '2') { final_role = ROLE_DOCTOR; valid_selection = 1; }
		else if (raw_opt[0] == '3') { final_role = ROLE_ADMIN; valid_selection = 1; }
		else {
			printf("\n [!] Opcion '%s' no valida. Intente de nuevo.\n", raw_opt);
			system("pause");
		}
	}
	
	printf("\n"); // Espacio visual
	
	// --- AHORA PEDIMOS DATOS ---
	char new_user[20], new_pass[20];
	int exists = 0;
	
	do {
		// Como usamos get_clean_input arriba, el buffer esta limpio.
		// Ya no se saltara esta pregunta.
		get_clean_input(new_user, 20, "Cree su Usuario: ");
		
		exists = 0;
		if (strlen(new_user) < 3) {
			printf("  [!] Usuario muy corto.\n");
			exists = 1;
			continue; // Vuelve a preguntar
		}
		
		for(int i=0; i<total_users_auth; i++) {
			if(strcmp(temp_users[i].username, new_user) == 0) {
				printf("  [!] El usuario '%s' ya existe.\n", new_user);
				exists = 1;
			}
		}
	} while(exists);
	
	get_clean_input(new_pass, 20, "Cree su Contrasena: ");
	
	// Guardar
	strcpy(temp_users[total_users_auth].username, new_user);
	strcpy(temp_users[total_users_auth].password, new_pass);
	temp_users[total_users_auth].role_id = final_role;
	total_users_auth++;
	
	printf("\n [OK] Cuenta registrada con exito.\n");
	system("pause");
}

int sub_handle_login(char *logged_user_id_out) {
	char input_user[20], input_pass[20];
	draw_auth_header("INICIAR SESION");
	
	get_clean_input(input_user, 20, "Usuario: ");
	get_clean_input(input_pass, 20, "Contrasena: ");
	
	for (int i = 0; i < total_users_auth; i++) {
		if (strcmp(input_user, temp_users[i].username) == 0 &&
			strcmp(input_pass, temp_users[i].password) == 0) {
			
			strcpy(logged_user_id_out, temp_users[i].username);
			return temp_users[i].role_id;
		}
	}
	return ROLE_NONE;
}

int core_perform_login(char *logged_user_id_out) {
	char option_buff[10]; // Usamos buffer en lugar de char simple para mas seguridad
	while (1) {
		draw_auth_header("BIENVENIDO");
		printf("   [a] Iniciar Sesion\n");
		printf("   [b] Registrarse (Crear Cuenta)\n");
		printf("   [q] Salir\n");
		printf(" *************************************************\n");
		
		get_clean_input(option_buff, 10, "Seleccione: ");
		char option = tolower(option_buff[0]);
		
		if (option == 'a') {
			int role = sub_handle_login(logged_user_id_out);
			if (role != ROLE_NONE) return role;
			else { printf("\n [!] Datos incorrectos.\n"); system("pause"); }
		}
		else if (option == 'b') sub_handle_register();
		else if (option == 'q') exit(0);
	}
}
