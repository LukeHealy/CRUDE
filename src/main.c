#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "io.h"
#include "db_handler.h"

int main(int argc, char const *argv[])
{
	int choice;
    while((choice = show_menu()) < 0);

    menu_action action = menu_action_factory(choice);

    action();




    return EXIT_SUCCESS;
}

int show_menu(void)
{
    int choice = -1;

    printf("Welcome to CRUDE, please select an option:\n\n");
    printf("    1: Load Database\n");
    printf("    2: Display Employee Record\n");
    printf("    3: Add Employee\n");
    printf("    4: Edit Employee\n");
    printf("    5: Delete Employee\n");
    printf("    6: Save Database\n");
    printf(">>> ");

    read_int_stdin(&choice);

    return choice > 6 ? -1 : choice;
}
