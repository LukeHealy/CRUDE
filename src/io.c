#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"

int read_int_stdin(int* i)
{
    if(scanf("%9d", i) > 0)
    {
        consume_stdin();
        return EXIT_SUCCESS;
    }
    consume_stdin();    

    return EXIT_FAILURE;
}

int read_string_stdin(char* buffer, int len)
{
    char pre_buffer[1024];
    int num_read = 0;

    if(buffer != NULL && len < 1024)
    {
        if((num_read = scanf("%1023s", pre_buffer)) > - 1)
        {
            consume_stdin();
            pre_buffer[1023] = '\0';
            strncpy(buffer, pre_buffer, len - 1);
            buffer[len - 1] = '\0';

            return EXIT_SUCCESS;
        }
    }

    return EXIT_FAILURE;
}

void consume_stdin(void)
{
    char c;
    while((c = fgetc(stdin)) != EOF && c != '\n');
}