#pragma once

int load_db(void);
int display_emp_rec(void);
int add_emp(void);
int edit_emp(void);
int delete_emp(void);
int save_db(void);

typedef int (*menu_action)(void);

menu_action menu_action_factory(int);