#pragma once
#include "employee.h"

typedef int (*print_func)(employee  emp[1000], char*);

/**
 * Holds the information for the save database
 * behaviour. 
 */
typedef struct save_data
{
    char file_path[256];
    print_func func;
} save_data;

int read_int_stdin(int* num);
int read_string_stdin(char* buffer, int len);
void consume_stdin(void);
