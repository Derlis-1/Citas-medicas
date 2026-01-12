#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/pacientes.h"
#include "../include/validaciones.h"

UserRecord db_patients[MAX_USERS];
int total_patients = 0;

int fn_search_user_index(const char *target_id) {
	for(int i = 0; i < total_patients; i++) {
		if(strcmp(db_patients[i].dni_id, target_id) == 0) return i;
	}
	return -1;
}

void sub_reg_patient() {
	if (total_patients >= MAX_USERS) {
		printf(" [!] Error: Base de datos llena.\n"); system("pause"); return;
	}
	UserRecord new_node; int valid = 0;
	printf("\n --- REGISTRO DE NUEVO PACIENTE ---\n");
	do {
		get_clean_input(new_node.dni_id, 11, "Cedula/DNI: ");
		if (!verify_ecuador_id(new_node.dni_id)) printf("  [!] Error: Documento invalido.\n");
		else if (fn_search_user_index(new_node.dni_id) != -1) printf("  [!] Error: Paciente ya registrado.\n");
		else valid = 1;
	} while (!valid);
	
	get_clean_input(new_node.full_name, 60, "Nombre Completo: ");
	
	// Validacion Edad
	do {
		new_node.current_age = get_safe_int("Edad: ");
		if (new_node.current_age <= 0 || new_node.current_age > 120) 
			printf("  [!] Edad no valida. Intente de nuevo.\n");
	} while (new_node.current_age <= 0 || new_node.current_age > 120);
	
	get_clean_input(new_node.phone_contact, 15, "Telefono: ");
	get_clean_input(new_node.email_addr, 50, "Email: ");
	new_node.is_active_flag = 1;
	db_patients[total_patients++] = new_node;
	printf(" [OK] Paciente guardado exitosamente.\n"); system("pause");
}

void sub_list_patients() {
	printf("\n --- REPORTE DE PACIENTES ACTIVOS ---\n");
	printf(" %-12s | %-25s | %-5s\n", "CEDULA", "NOMBRE", "EDAD");
	printf(" -------------------------------------------------\n");
	for(int i = 0; i < total_patients; i++) {
		if (db_patients[i].is_active_flag) {
			printf(" %-12s | %-25s | %-5d\n", db_patients[i].dni_id, db_patients[i].full_name, db_patients[i].current_age);
		}
	}
	printf(" -------------------------------------------------\n"); system("pause");
}

void core_patient_manager() {
	char op = ' ';
	while(tolower(op) != 'x') {
		system("cls");
		printf("\n [ MODULO DE GESTION: PACIENTES ]\n");
		printf("   a) Registrar nuevo paciente\n");
		printf("   b) Listar base de datos\n");
		printf("   x) Volver al panel anterior\n");
		printf(" --------------------------------\n");
		
		char buff[10];
		get_clean_input(buff, 10, ">> Opcion: ");
		op = tolower(buff[0]);
		
		if (op == 'a') sub_reg_patient(); else if (op == 'b') sub_list_patients();
	}
}

// --- FUNCION: PERFIL PERSONAL DEL PACIENTE (CORREGIDA) ---
void access_patient_profile(const char *my_id) {
	system("cls");
	printf("\n *************************************************\n");
	printf("   MI PERFIL PERSONAL | ID: %s\n", my_id);
	printf(" *************************************************\n");
	
	int index = fn_search_user_index(my_id);
	
	if (index != -1) {
		UserRecord p = db_patients[index];
		printf("\n   [ DATOS REGISTRADOS ]\n");
		printf("   --------------------------------\n");
		printf("   > Nombre:    %s\n", p.full_name);
		printf("   > Edad:      %d anios\n", p.current_age);
		printf("   > Telefono:  %s\n", p.phone_contact);
		printf("   > Email:     %s\n", p.email_addr);
		printf("   --------------------------------\n");
		printf("\n [OK] Sus datos estan actualizados.\n");
	} 
	else {
		printf("\n [!] Atencion: Su ficha medica esta vacia.\n");
		printf("     Para poder agendar citas, necesitamos sus datos.\n");
		printf("\n   Desea completar su perfil ahora?\n");
		printf("   1. Si, completar datos\n");
		printf("   2. No, mas tarde\n");
		
		int opt = get_safe_int(">> Opcion: ");
		
		if (opt == 1) {
			printf("\n   [ COMPLETANDO PERFIL ]\n");
			
			UserRecord new_p;
			strcpy(new_p.dni_id, my_id); 
			// Ya no muestra "(Bloqueado)", solo confirma el ID
			printf("   > ID Usuario: %s\n", new_p.dni_id);
			
			get_clean_input(new_p.full_name, 60, "   > Nombre Completo: ");
			
			// VALIDACION EDAD (Bucle)
			do {
				new_p.current_age = get_safe_int("   > Edad Actual: ");
				if (new_p.current_age <= 0 || new_p.current_age > 120) {
					printf("     [!] Error: Ingrese una edad valida (numeros).\n");
				}
			} while (new_p.current_age <= 0 || new_p.current_age > 120);
			
			// VALIDACION TELEFONO (Bucle numerico)
			int phone_ok = 0;
			do {
				get_clean_input(new_p.phone_contact, 15, "   > Telefono Celular: ");
				phone_ok = 1;
				// Revisamos caracter por caracter que sean numeros
				for(int i=0; i<strlen(new_p.phone_contact); i++) {
					if(!isdigit(new_p.phone_contact[i])) {
						phone_ok = 0;
						break;
					}
				}
				if (!phone_ok || strlen(new_p.phone_contact) < 7) {
					printf("     [!] Error: El telefono debe contener solo numeros.\n");
					phone_ok = 0;
				}
			} while(!phone_ok);
			
			get_clean_input(new_p.email_addr, 50, "   > Correo Email: ");
			new_p.is_active_flag = 1;
			
			if (total_patients < MAX_USERS) {
				db_patients[total_patients++] = new_p;
				printf("\n [OK] Perfil guardado exitosamente!\n");
			}
		}
	}
	system("pause");
}
