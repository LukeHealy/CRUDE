#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "main.h"
#include "io.h"
#include "db_handler.h"
#include "password.h"

/**
 * Initialise some the employee array and the password.
 * The loop the menu.
 */
int main(int argc, char const *argv[])
{
    int choice;
    int i;
    employee* emp = (employee*)malloc(sizeof(employee) * 1000);
    vault = (password*)malloc(sizeof(password));

    strncpy(vault->pass, "password", 9);

    for(i = 0; i < 1000; i++)
    {
        emp[i].id = 0;
    }

    printf("Welcome to CRUDE. ");

    MENU:

        while((choice = show_menu()) < 0);
        menu_action action = menu_action_factory(choice);
        action(emp);
    
    goto MENU;

    // Free the employee array at the end to avoid memory leaks.
    free(emp);

    return EXIT_SUCCESS;
}

/**
 * Runs until goo input, returns an int from 0 to 9, the coice.
 */
int show_menu(void)
{
    int choice = -1;
    printf("Please select an option:\n\n");
    printf("    0: Change Password\n");
    printf("    1: Load Database\n");
    printf("    2: Display Employee Record\n");
    printf("    3: Add Employee\n");
    printf("    4: Edit Employee\n");
    printf("    5: Delete Employee\n");
    printf("    6: Save Database\n");
    printf("    7: Discard Changes\n");
    printf("    8: Unload Database\n");
    printf("    9: Exit\n");
    printf(">>> ");

    read_int_stdin(&choice);

    return choice > 9 ? -1 : choice;
}
