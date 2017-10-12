#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "db_handler.h"
#include "io.h"

employee *backup_list;

int changes;

int load_db(employee emp[1000])
{
    char *filename = (char*)malloc(sizeof(char) * 256);

    backup_list = (employee*)malloc(sizeof(employee) * 1000);

    memset(emp, 0, 1000 * sizeof(employee));

    printf("Enter filename of the database:\n>>> ");
    read_string_stdin(filename, 256);

    if(read_csv(filename, emp) == EXIT_FAILURE)
    {
        fprintf(stderr, "Invalid file detected, nothing loaded.\n");
        memset(emp, 0, 1000 * sizeof(employee));

        free(filename);

        return EXIT_FAILURE;
    }
    
    memcpy(backup_list, emp, sizeof(employee) * 1000);
    changes = 0;

    free(filename);

    return EXIT_SUCCESS;
}

int unload_database(employee emp[1000])
{
    if(confirm_with_user("Are you sure you want to unload the database? (unsaved changes will be lost.)"))
    {
        memset(emp, 0, sizeof(employee) * 1000);
        changes = 0;
    }
    // Get rid of old backup, no longer needed.
    // Double free crash: here when db is loaded then unloaded twice.
    free(backup_list);

    return EXIT_SUCCESS;
}

int discard_changes(employee emp[1000])
{
    if(changes)
    {
        if(confirm_with_user("Are you sure you want to discard changes?"))
        {
            memcpy(emp, backup_list, sizeof(employee) * 1000);
            changes = 0;
        }
    }
    else
    {
        printf("No changes to discard.\n");
    }

    return EXIT_SUCCESS;
}


int display_emp_rec(employee emp[1000])
{
    int emp_id = 0;
    employee* temployee;
    printf("Enter an employee ID:\n>>> ");

    while(read_int_stdin(&emp_id) != EXIT_SUCCESS)
    {
        printf("Invalid.\nEnter an employee ID:\n>>> ");
    }

    if((temployee = get_employee_by_id(emp, emp_id)) != NULL)
    {
        print_employee(temployee);
    }
    else
    {
        printf("No employee with ID %d.\n", emp_id);
    }

    return EXIT_SUCCESS;
}

int get_num_employees(employee emp[1000])
{
    int i = 0;
    while(emp[i].id != 0)
    {
        i++;
    }

    return i;
}

int get_detail_from_user(employee** emp, int word_len, char* prompt, int idx, int num_employees)
{
    char item[1024];

    printf("%s\n", prompt);
    read_string_stdin(item, word_len);
    return store_word(item, word_len, *emp, idx, num_employees);
}

int update_employee(employee* emp, int num_employees)
{
    employee* backup = (employee*)malloc(sizeof(employee));
    /*Memory leak 3, if employee is null, backup isnt freed.*/
    memcpy(backup, emp, sizeof(employee));

    if(emp == NULL)
    {
        printf("Unable to update, no employee with that ID.\n");
        return EXIT_FAILURE;
    }
    // Heap overflow corruption: position has a typo allowing 150 characters instead of 15. this corrupts
    // the salary and the next employee id generated.
    if(get_detail_from_user(&emp, 3, "Enter employee's salutation:\n>>> ", 1, num_employees)
    || get_detail_from_user(&emp, 20, "Enter employee's first name:\n>>> ", 2, num_employees)
    || get_detail_from_user(&emp, 30, "Enter employee's surname:\n>>> ", 3, num_employees)
    || get_detail_from_user(&emp, 150, "Enter employee's position:\n>>> ", 4, num_employees)
    || get_detail_from_user(&emp, 9, "Enter employee's salary:\n>>> ", 5, num_employees)
    || !confirm_with_user("Are you sure you want to update this employee?"))
    {
        printf("Employee not saved.\n");
        memcpy(emp, backup, sizeof(employee));

        free(backup);

        return EXIT_FAILURE;
    }
    
    emp->deleted = 0;

    free(backup);

    changes = 1;

    return EXIT_SUCCESS;
}

int generate_unique_id(employee emp[1000])
{
    int i;
    int max_id = 0;

    for(i = 0; i < 1000; i++)
    {
        max_id = emp[i].id > max_id ? emp[i].id : max_id;
    }

    return max_id + 1;
}

int add_emp(employee emp[1000])
{
    int new_id = generate_unique_id(emp);
    int num_emp = get_num_employees(emp);

    printf("New employee created with ID: %d\n", new_id);
    emp[num_emp].id = new_id;

    if(update_employee(&emp[num_emp], num_emp))
    {
        emp[num_emp].id = 0;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int edit_emp(employee emp[1000])
{
    int id = 0;
    employee* temployee;
    printf("Enter employee ID to edit:\n>>> ");

    while(read_int_stdin(&id) != EXIT_SUCCESS)
    {
        printf("Invalid, Enter employee ID to edit:\n>>> ");
    }

    temployee = get_employee_by_id(emp, id);

    update_employee(temployee, get_num_employees(emp));

    return EXIT_SUCCESS;
}

int delete_emp(employee emp[1000])
{
    int emp_id = 0;
    employee* temployee;
    printf("Enter employee ID to delete:\n>>> ");

    changes = 1;

    while(read_int_stdin(&emp_id) != EXIT_SUCCESS)
    {
        printf("Invalid, Enter employee ID to delete:\n>>> ");
    }

    if((temployee = get_employee_by_id(emp, emp_id)) != NULL)
    {
        printf("Deleting %s %s.\n", temployee->firstname, temployee->surname);
        if(authenticate_user())
        {
            temployee->deleted = 1;
        }
        else
        {
            printf("Password incorrect, employee unchanged.\n");
            return EXIT_FAILURE;
        }
    }
    else
    {
        printf("No employee with ID %d.\n", emp_id);
        changes = 0;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

typedef struct save_data
{
    char file_path[16];
    print_func func;
} save_data;

int save_db(employee emp[1000])
{
    /*Leak 1. This leaks when write_db_to_file fails. */
    save_data* sd = (save_data*)malloc(sizeof(save_data));
    //sd->file_path = (char*)malloc(16);

    int choice = 0;

    printf("Print database.\n");
    printf("1: To a file.\n");
    printf("2: To the screen.\n>>> ");

    read_int_stdin(&choice);    

    while(choice != 1 && choice != 2)
    {   
        printf("Error, enter 1 or 2.\n>>> ");
        read_int_stdin(&choice);
    }

    if(choice == 2)
    {
        sd->func = &write_db_to_screen;
    }
    else if(choice == 1)
    {
        // Heap overflow 1:
        sd->func = &write_db_to_file;
        printf("Enter the path to save the database file.\n>>> ");
        scanf("%s", sd->file_path);
    }

    if((sd->func)(emp, sd->file_path) == EXIT_SUCCESS)
    {
        printf("Action successful.\n");
    }
    else
    {
        printf("Error, Database not written to file.\n");
        free(sd);
        return EXIT_FAILURE;
    }

    free(sd->file_path);
    free(sd);

    return EXIT_SUCCESS;
}

int write_db_to_screen(employee emp[1000], char* path)
{
    int i;
    for(i = 0; i < get_num_employees(emp); i++)
    {
        print_employee(&emp[i]);
    }

    return EXIT_SUCCESS;
}

int write_db_to_file(employee emp[1000], char* path)
{
    int i;
    FILE* f = (FILE*)malloc(sizeof(FILE));

    f = fopen(path, "w");

    if(f == NULL)
    {
        perror(path);
        return EXIT_FAILURE;
    }

    for(i = 0; i < get_num_employees(emp); i++)
    {
        fprintf(f, "%d,%s,%s,%s,%s,%d,%d\n", 
            emp[i].id,
            emp[i].salutation,
            emp[i].firstname,
            emp[i].surname,
            emp[i].position,
            emp[i].salary,
            emp[i].deleted);
    }

    fclose(f);


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
        case 7:
            return &discard_changes;
        case 8:
            return &unload_database;
        case 9:
            return &exit_program;
    }
    return NULL;
}

int exit_program(employee emp[1000])
{
    if(confirm_with_user("Are you sure you want to quit?"))
    {
        free(emp);
        exit(EXIT_SUCCESS);
    }

    return 0;
}

int print_employee(employee* emp)
{
    if(emp != NULL)
    {
        printf("Employee %d: %s %s %s, %s. Salary: $%d. Deleted: %d\n",
            emp->id,
            emp->salutation,
            emp->firstname,
            emp->surname,
            emp->position,
            emp->salary,
            emp->deleted);
    }

    return EXIT_SUCCESS;
}

employee* get_employee_by_id(employee emp[1000], int id)
{
    int i = 0;

    while(i < 1000)
    {
        if(emp[i].id == id)
        {
            return &emp[i];
        }
        i++;
    }

    return NULL;
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
            if(sscanf(current_word, "%d", &(emp->id)) != 1 || emp->id < 0)
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
                strncpy(emp->salutation, current_word, curr_word_len);
            }
            else
            {
                printf("Invalid Salutation on line %d: \n", num_read);
                return EXIT_FAILURE;
            }

            break;
        case 2:
            strncpy(emp->firstname, current_word, curr_word_len + 1);
            break;
        case 3:
            strncpy(emp->surname, current_word, curr_word_len + 1);
            break;
        case 4:
            strncpy(emp->position, current_word, curr_word_len + 1);
            break;
        case 5:
            if(sscanf(current_word, "%d", &(emp->salary)) != 1 || emp->salary <= 0)
            {
                printf("Invalid Salary on line %d: \n", num_read);
                return EXIT_FAILURE;
            }
            break;
        case 6:
            if(sscanf(current_word, "%d", &(emp->deleted)) != 1)
            {
                printf("Invalid Deleted on line %d: \n", num_read);
                return EXIT_FAILURE;
            }
            if(emp->deleted != 1 && emp->deleted != 0)
            {
                printf("Invalid Deleted on line %d: \n", num_read);
                return EXIT_FAILURE;
            }
            break;
    }
    return EXIT_SUCCESS;
}

int confirm_with_user(char* msg)
{
    printf("%s [y/N]\n>>> ", msg);
    char *verdict = (char*)malloc(2 * sizeof(char)); 
    //leak 2. If max tries is reached verdict isn't freed

    int max_tries = 5;
    int count = 0;

    while(read_string_stdin(verdict, 2) != EXIT_SUCCESS || (strncmp(verdict, "y", 1) != 0 && strncmp(verdict, "n", 1) != 0))
    {
        count++;

        if(count >= max_tries)
        {   
            printf("Max tried exceeded.\n");
            return 0;
        }

        printf("Please enter y or n.\n>>> ");
    }

    if(count < max_tries && (strncmp("y", verdict, 1) == 0))
    {
        free(verdict);
        return 1;
    }

    free(verdict);

    return 0;
}

/**
 * Very secure authentication for security.
 * Passwords are limmited to 8 characters.
 */
int authenticate_user(void)
{
    char unhackable[9] = "password";
    char password[9];

    printf("Enter password:\n>>> ");
    // Stack smash 1: This is a stack based buffer overflow resulting in code exec/crash.
    // can also bypass password auth.
    scanf("%s", password);

    /* We only need to compare 8 characters as that's the password
     * length limit.
     */
    if(strncmp(password, unhackable, 8) == 0)
    {
        return 1;
    }

    return 0;
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

            if(store_word(current_word, curr_word_len, &emp[num_read], num_matched, num_read))
            {
                free(current_word);
                return EXIT_FAILURE;
            }
            
            free(current_word);
        }
                
        num_read++;
    }


    fclose(csv_file);
    return EXIT_SUCCESS;
}
