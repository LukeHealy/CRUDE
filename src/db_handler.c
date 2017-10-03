#include <stdlib.h>
#include <stdio.h>

#include "db_handler.h"

int load_db(void)
{
	printf("Loading Database...\n");
	return EXIT_SUCCESS;
}

int display_emp_rec(void)
{
	printf("Display Employee records\n");
	return EXIT_SUCCESS;
}

int add_emp(void)
{
	printf("Add Employee\n");
	return EXIT_SUCCESS;
}

int edit_emp(void)
{
	printf("Edit Employee\n");
	return EXIT_SUCCESS;
}

int delete_emp(void)
{
	printf("Delete Employee\n");
	return EXIT_SUCCESS;
}

int save_db(void)
{
	printf("Save Database\n");
	return EXIT_SUCCESS;
}

menu_action menu_action_factory(int choice)
{
	switch(choice)
	{
		case 1:
			return &load_db;
		case 2:
			return &display_emp_rec;
		case 3:
			return &add_emp;
		case 4:
			return &edit_emp;
		case 5:
			return &delete_emp;
		case 6:
			return &save_db;
	}
	return NULL;	
}