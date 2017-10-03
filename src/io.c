#include <stdio.h>
#include <stdlib.h>

#include "io.h"

int read_int_stdin(int* i)
{
    char raw_input[10];

    if(fgets(raw_input, sizeof(raw_input), stdin))
    {
        consume_stdin();
        if(sscanf(raw_input, "%d", i) == 1)
        {
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