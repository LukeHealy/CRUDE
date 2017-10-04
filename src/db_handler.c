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

    if(read_csv(filename, emp) == EXIT_FAILURE)
    {
        fprintf(stderr, "Invalid file detected, nothing loaded.\n");
        return EXIT_FAILURE;
    }

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

int get_word_len(int num)
{
    switch(num)
    {
        case 0:
            return 9;
        case 1:
            return 3;
        case 2:
            return 20;
        case 3:
            return 30;
        case 4:
            return 15;
        case 5:
            return 9;
        case 6:
            return 1;
    }
    return 0;
}

int store_word(char* current_word, int curr_word_len, employee* emp, int num_matched, int num_read)
{
    switch(num_matched)
    {
        case 0:
            if(sscanf(current_word, "%d", &emp[num_read].id) != 1)
            {
                printf("Invalid ID on line %d: \n", num_read);
                return EXIT_FAILURE;
            }
            break;
        case 1:
            if(strncmp(current_word, "Mr", curr_word_len) == 0 ||
                strncmp(current_word, "Mrs", curr_word_len) == 0 ||
                strncmp(current_word, "Ms", curr_word_len) == 0 ||
                strncmp(current_word, "Sir", curr_word_len) == 0 ||
                strncmp(current_word, "Mdm", curr_word_len) == 0)
            {
                strncpy(emp[num_read].salutation, current_word, curr_word_len);
            }
            else
            {
                printf("Invalid Salutation on line %d: \n", num_read);
                return EXIT_FAILURE;
            }

            break;
        case 2:
            strncpy(emp[num_read].firstname, current_word, curr_word_len + 1);
            break;
        case 3:
            strncpy(emp[num_read].surname, current_word, curr_word_len + 1);
            break;
        case 4:
            strncpy(emp[num_read].position, current_word, curr_word_len + 1);
            break;
        case 5:
            if(sscanf(current_word, "%d", &emp[num_read].salary) != 1)
            {
                printf("Invalid Salary on line %d: \n", num_read);
                return EXIT_FAILURE;
            }
            break;
        case 6:
            if(sscanf(current_word, "%d", &emp[num_read].deleted) != 1)
            {
                printf("Invalid Deleted on line %d: \n", num_read);
                return EXIT_FAILURE;
            }
            if(emp[num_read].deleted != 1 && emp[num_read].deleted != 0)
            {
                printf("Invalid Deleted on line %d: \n", num_read);
                return EXIT_FAILURE;
            }
            break;
    }
    return EXIT_SUCCESS;
}

int read_csv(char* filename, employee* emp)
{
    char temp_line[128] = {0};
    int num_read = 0;
    int curr_word_len = 0;

    FILE* csv_file = fopen(filename, "r");

    if(csv_file == NULL)
    {
        perror(filename);
        return EXIT_FAILURE;
    }

    while(fgets(temp_line, 128, csv_file) != NULL && num_read < 1000)
    {
        int num_matched;
        int idx = 0;
        char* current_word;

        for(num_matched = 0; num_matched < 7; num_matched++)
        {
            int i = 0;
            curr_word_len = get_word_len(num_matched);
            current_word = (char*)malloc(sizeof(char) * (curr_word_len + 1));
            
            while(temp_line[idx] != ',' && temp_line[idx] != '\0' && i < curr_word_len && idx < 128)
            {
                current_word[i] = temp_line[idx];
                i++;
                idx++;
                if(num_matched == 6)
                {
                    break;
                }
            }

            if(i == curr_word_len && num_matched < 6)
            {
                while(temp_line[idx] != ',' && idx < 128)
                {
                    idx++;
                }
            }
            else if(i == 0)
            {
                printf("Blank value: \n");
                return EXIT_FAILURE;
            }

            if(idx == 128)
            {
                printf("Line too long: \n");
                return EXIT_FAILURE;
            }

            idx++;
            current_word[i] = '\0';

            store_word(current_word, curr_word_len, emp, num_matched, num_read);
            
            free(current_word);
        }
                
        num_read++;
    }


    fclose(csv_file);
    return EXIT_SUCCESS;
}
