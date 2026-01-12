#ifndef CITAS_H
#define CITAS_H

#define MAX_CITAS 200

typedef struct {
	int id_cita;            // Un numero unico para identificar la cita (1, 2, 3...)
	char patient_id[20];    // ID del paciente (ej. "pansito")
	char doctor_code[10];   // Codigo del medico (ej. "DOC01")
	char date_time[20];     // Fecha y Hora (ej. "10-05-2024 10:00")
	char reason[100];       // Motivo de la consulta
	int status;             // 0: Pendiente, 1: Completada, 2: Cancelada
} AppointmentRecord;

// Funciones Administrativas
void core_citas_manager(); 

// Funciones del Paciente
void patient_request_appointment(const char *my_id); // El paciente pide cita
void patient_view_appointments(const char *my_id);   // El paciente ve sus citas

#endif
