#pragma once

#include "employee.h"

typedef int (*menu_action)(employee emp[1000]);

int load_db(employee emp[1000]);
int display_emp_rec(employee emp[1000]);
int add_emp(employee emp[1000]);
int edit_emp(employee emp[1000]);
int delete_emp(employee emp[1000]);
int save_db(employee emp[1000]);
menu_action menu_action_factory(int choice);
int read_csv(char* filename, employee* emp);
employee* get_employee_by_id(employee emp[1000], int id);
int print_employee(employee* emp);
int get_word_len(int num);
int store_word(char* current_word, int curr_word_len, employee* emp, int num_matched, int num_read);
