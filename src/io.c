#include <stdio.h>
#include <stdlib.h>

#include "io.h"

int read_int_stdin(int* i)
{
    if(scanf("%9d", i) > -1)
    {
        consume_stdin();
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

void consume_stdin(void)
{
    char c;
    while((c = fgetc(stdin)) != EOF && c != '\n');
}