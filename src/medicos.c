#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/medicos.h"
#include "../include/validaciones.h"

// --- MEDICOS PRE-CARGADOS (Para que no salga vacio al probar) ---
StaffRecord db_staff[MAX_STAFF] = {
	{"DOC1", "Dr. Gregory House", "Diagnostico", "08:00-16:00"},
{"DOC2", "Dra. Meredith Grey", "Cirugia General", "09:00-18:00"}
};
int total_staff = 2; // Iniciamos en 2 porque ya hay 2 registrados

int fn_find_staff(const char *code) {
	for(int i=0; i < total_staff; i++) {
		if(strcmp(db_staff[i].staff_code, code) == 0) return i;
	}
	return -1;
}

void sub_reg_staff() {
	if(total_staff >= MAX_STAFF) return;
	
	StaffRecord doctor;
	int is_unique = 0;
	
	printf("\n --- ALTA DE PERSONAL MEDICO ---\n");
	
	// CORRECCION AQUI:
	// Si venimos de un menu con scanf, puede haber basura. 
	// Como usamos get_clean_input, aseguramos el input.
	
	do {
		// Pedimos el codigo
		get_clean_input(doctor.staff_code, 10, "Codigo ID (ej. DOC-01): ");
		
		// Validacion 1: Longitud (Evita que el 'Enter' fantasma moleste)
		if (strlen(doctor.staff_code) < 2) {
			// Si esta vacio o muy corto, simplemente ignoramos o avisamos sutilmente
			// sin hacer tanto escandalo, y volvemos a pedir.
			continue; 
		}
		
		// Validacion 2: Unicidad
		if(fn_find_staff(doctor.staff_code) != -1) {
			printf("  [!] Error: Ese codigo ya existe.\n");
		} else {
			is_unique = 1;
		}
	} while(!is_unique);
	
	get_clean_input(doctor.name_tag, 60, "Nombre Doctor(a): ");
	get_clean_input(doctor.specialty, 50, "Especialidad: ");
	get_clean_input(doctor.work_hours, 20, "Horario (HH:MM-HH:MM): ");
	
	db_staff[total_staff++] = doctor;
	printf(" [OK] Medico registrado.\n");
	system("pause");
}

void sub_list_staff() {
	printf("\n --- PLANTILLA DE MEDICOS ---\n");
	printf(" %-10s | %-20s | %-15s\n", "CODIGO", "NOMBRE", "ESPECIALIDAD");
	printf(" --------------------------------------------------\n");
	for(int i=0; i<total_staff; i++) {
		printf(" %-10s | %-20s | %-15s\n", 
			   db_staff[i].staff_code, db_staff[i].name_tag, db_staff[i].specialty);
	}
	printf(" --------------------------------------------------\n");
	system("pause");
}

void core_staff_manager() {
	char op = ' ';
	while(tolower(op) != 'x') {
		system("cls");
		printf("\n [ MODULO STAFF MEDICO ]\n");
		printf("   a) Nuevo ingreso\n");
		printf("   b) Ver plantilla\n");
		printf("   x) Volver\n");
		printf(" ----------------------\n");
		
		// USAMOS get_clean_input para el menu tambien (Evita bugs de buffer)
		char buff[10];
		get_clean_input(buff, 10, ">> Opcion: ");
		op = tolower(buff[0]);
		
		if (op == 'a') sub_reg_staff();
		else if (op == 'b') sub_list_staff();
	}
}

