#ifndef PACIENTES_H
#define PACIENTES_H

#define MAX_USERS 150 
#include "../include/pacientes.h"
#include "../include/medicos.h"
#include "../include/citas.h"

typedef struct {
	char dni_id[20];
	char full_name[60];
	int current_age;
	char phone_contact[15];
	char email_addr[50];
	int is_active_flag;
} UserRecord;

void core_patient_manager();
void sub_reg_patient();
void sub_list_patients();
int fn_search_user_index(const char *target_id);

void access_patient_profile(const char *my_id);
#endif
