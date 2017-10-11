#pragma once

#include "employee.h"

typedef int (*menu_action)(employee emp[1000]);
typedef int (*print_func)(employee  emp[1000], char*);


int load_db(employee emp[1000]);
int display_emp_rec(employee emp[1000]);
int add_emp(employee emp[1000]);
int edit_emp(employee emp[1000]);
int delete_emp(employee emp[1000]);
int save_db(employee emp[1000]);
int discard_changes(employee emp[1000]);
int exit_program(employee emp[1000]);
menu_action menu_action_factory(int choice);
int read_csv(char* filename, employee* emp);
employee* get_employee_by_id(employee emp[1000], int id);
int print_employee(employee* emp);
int get_word_len(int num);
int store_word(char* current_word, int curr_word_len, employee* emp, int num_matched, int num_read);
int generate_unique_id(employee emp[1000]);
int update_employee(employee* emp, int num_employees);
int get_detail_from_user(employee** emp, int word_len, char* prompt, int idx, int num_employees);
int confirm_with_user(char* msg);
int authenticate_user(void);
int write_db_to_file(employee emp[1000], char* path);
int unload_database(employee emp[1000]);
int write_db_to_screen(employee emp[1000], char* path);
