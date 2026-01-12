#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/citas.h"
#include "../include/validaciones.h"
#include "../include/medicos.h"

// Base de datos de Citas
AppointmentRecord db_appointments[MAX_CITAS];
int total_appointments = 0;
int next_id_counter = 1;

// Importamos acceso a medicos
extern StaffRecord db_staff[]; 
extern int total_staff;
extern int fn_find_staff(const char *code);

// --- UTILIDAD: Mostrar lista de medicos ---
void helper_show_doctors() {
	printf("   ------------------------------------------------\n");
	printf("   DOCTORES DISPONIBLES:\n");
	printf("   %-10s | %-20s | %-15s\n", "CODIGO", "NOMBRE", "ESPECIALIDAD");
	printf("   ------------------------------------------------\n");
	for(int i=0; i<total_staff; i++) {
		printf("   %-10s | %-20s | %-15s\n", 
			   db_staff[i].staff_code, db_staff[i].name_tag, db_staff[i].specialty);
	}
	printf("   ------------------------------------------------\n");
}

// --- PACIENTE: SOLICITAR CITA ---
void patient_request_appointment(const char *my_id) {
	if (total_appointments >= MAX_CITAS) {
		printf(" [!] Agenda llena.\n"); system("pause"); return;
	}
	system("cls");
	printf("\n *************************************************\n");
	printf("   NUEVA SOLICITUD DE CITA\n");
	printf(" *************************************************\n");
	
	if (total_staff == 0) {
		printf(" [!] No hay medicos registrados aun.\n"); system("pause"); return;
	}
	helper_show_doctors();
	
	AppointmentRecord new_app;
	int doc_found = 0;
	do {
		get_clean_input(new_app.doctor_code, 10, ">> Ingrese CODIGO del doctor: ");
		if (fn_find_staff(new_app.doctor_code) != -1) doc_found = 1;
		else printf("   [!] Codigo incorrecto.\n");
	} while (!doc_found);
	
	get_clean_input(new_app.date_time, 20, ">> Fecha (DD-MM-AAAA): ");
	get_clean_input(new_app.reason, 100, ">> Motivo: ");
	
	new_app.id_cita = next_id_counter++;
	strcpy(new_app.patient_id, my_id);
	new_app.status = 0; // 0: Activa/Pendiente
	
	db_appointments[total_appointments++] = new_app;
	printf("\n [OK] Cita #%d creada con exito.\n", new_app.id_cita);
	system("pause");
}

// --- PACIENTE: VER SUS CITAS ---
void patient_view_appointments(const char *my_id) {
	system("cls");
	printf("\n *************************************************\n");
	printf("   MIS CITAS | PACIENTE: %s\n", my_id);
	printf(" *************************************************\n");
	printf(" %-4s | %-10s | %-12s | %-20s\n", "ID", "DOCTOR", "FECHA", "ESTADO");
	printf(" --------------------------------------------------------\n");
	
	int found = 0;
	for(int i=0; i<total_appointments; i++) {
		if (strcmp(db_appointments[i].patient_id, my_id) == 0) {
			char status_txt[15];
			if(db_appointments[i].status == 0) strcpy(status_txt, "ACTIVA");
			else strcpy(status_txt, "CANCELADA");
			
			printf(" %-4d | %-10s | %-12s | %-20s\n", 
				   db_appointments[i].id_cita,
				   db_appointments[i].doctor_code,
				   db_appointments[i].date_time,
				   status_txt);
			found++;
		}
	}
	if(found == 0) printf("  [i] No tiene citas.\n");
	printf(" --------------------------------------------------------\n");
	system("pause");
}

// --- ADMINISTRADOR: GESTION TOTAL ---
void sub_admin_list_all() {
	printf("\n --- REPORTE GLOBAL DE CITAS ---\n");
	printf(" %-4s | %-10s | %-10s | %-10s\n", "ID", "PACIENTE", "DOCTOR", "ESTADO");
	printf(" --------------------------------------------\n");
	for(int i=0; i<total_appointments; i++) {
		char st[10];
		if(db_appointments[i].status == 0) strcpy(st, "OK");
		else strcpy(st, "CANCEL");
		
		printf(" %-4d | %-10s | %-10s | %-10s\n", 
			   db_appointments[i].id_cita,
			   db_appointments[i].patient_id,
			   db_appointments[i].doctor_code,
			   st);
	}
	printf(" --------------------------------------------\n");
	system("pause");
}

void sub_admin_cancel_app() {
	int target_id = get_safe_int(">> Ingrese el ID de la cita a cancelar: ");
	int found = 0;
	for(int i=0; i<total_appointments; i++) {
		if (db_appointments[i].id_cita == target_id) {
			db_appointments[i].status = 1; // 1 = Cancelado
			printf(" [OK] La cita #%d ha sido cancelada.\n", target_id);
			found = 1;
			break;
		}
	}
	if(!found) printf(" [!] No se encontro esa cita.\n");
	system("pause");
}

void core_citas_manager() {
	char op = ' ';
	while(tolower(op) != 'x') {
		system("cls");
		printf("\n [ ADMIN - CONTROL DE CITAS ]\n");
		printf("   a) Ver todas las citas (Reporte Global)\n");
		printf("   b) Cancelar una cita\n");
		printf("   x) Volver\n");
		printf(" ----------------------------\n");
		
		char buff[10];
		get_clean_input(buff, 10, ">> Opcion: ");
		op = tolower(buff[0]);
		
		if(op == 'a') sub_admin_list_all();
		else if(op == 'b') sub_admin_cancel_app();
	}
}
