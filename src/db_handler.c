#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "db_handler.h"
#include "io.h"

int load_db(employee emp[1000])
{
    char filename[256];

    printf("Enter filename of the database:\n>>> ");
    read_string_stdin(filename, 256);

    read_csv(filename, emp);

    return EXIT_SUCCESS;
}

int display_emp_rec(employee emp[1000])
{
    int emp_id = 0;
    printf("Enter an employee ID:\n>>> ");

    while(read_int_stdin(&emp_id) != EXIT_SUCCESS)
    {
        printf("Invalid.\nEnter an employee ID:\n>>> ");
    }

    print_employee(get_employee_by_id(emp, emp_id));

    return EXIT_SUCCESS;
}

int add_emp(employee emp[1000])
{
    printf("Add Employee\n");
    return EXIT_SUCCESS;
}

int edit_emp(employee emp[1000])
{
    printf("Edit Employee\n");
    return EXIT_SUCCESS;
}

int delete_emp(employee emp[1000])
{
    printf("Delete Employee\n");
    return EXIT_SUCCESS;
}

int save_db(employee emp[1000])
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

int print_employee(employee* emp)
{
    printf("Employee %d: %s %s %s, %s. Salary: $%d. Deleted: %d\n",
        emp->id,
        emp->salutation,
        emp->firstname,
        emp->surname,
        emp->position,
        emp->salary,
        emp->deleted);

    return EXIT_SUCCESS;
}

employee* get_employee_by_id(employee emp[1000], int id)
{
    int i = 0;
    while(emp[i].id != id && i < 1000)
    {
        i ++;
    }
    return &emp[i];
}


int read_csv(char* filename, employee* emp)
{
    char temp_line[128];
    int num_read = 0;

    FILE* csv_file = fopen(filename, "r");

    if(csv_file == NULL)
    {
        perror(filename);
        return EXIT_FAILURE;
    }

    while(fgets(temp_line, 128, csv_file) != NULL)
    {
        int num_matched;
        int idx = 0;
        char current_word[31];

        for(num_matched = 0; num_matched < 7; num_matched++)
        {
            int i = 0;
            while(temp_line[idx] != ',' && temp_line[idx] != '\0' && i < 30 && idx < 128)
            {
                current_word[i] = temp_line[idx];
                i++;
                idx++;
            }

            idx++;
            current_word[i] = '\0';

            switch(num_matched)
            {
                case 0:
                    emp[num_read].id = atoi(current_word);
                    break;
                case 1:
                    strncpy(emp[num_read].salutation, current_word, 3);
                    break;
                case 2:
                    strncpy(emp[num_read].firstname, current_word, 21);
                    break;
                case 3:
                    strncpy(emp[num_read].surname, current_word, 31);
                    break;
                case 4:
                    strncpy(emp[num_read].position, current_word, 16);
                    break;
                case 5:
                    emp[num_read].salary = atoi(current_word);
                    break;
                case 6:
                    emp[num_read].deleted = atoi(current_word);
                    break;
            }
        }
                
        num_read++;
    }


    fclose(csv_file);
    return EXIT_SUCCESS;
}
