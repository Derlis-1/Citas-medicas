#ifndef MEDICOS_H
#define MEDICOS_H

#define MAX_STAFF 50

typedef struct {
	char staff_code[10];
	char name_tag[60];
	char specialty[50];
	char work_hours[20];
} StaffRecord;

void core_staff_manager();
void sub_reg_staff();
void sub_list_staff();
int fn_find_staff(const char *code);

#endif
