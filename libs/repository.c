#include "repository.h"
#include <stdio.h>
#include <string.h>

short line_count(char* fileName)
{
    fileName[strcspn(fileName, "\n")] = 0;
    FILE *ptr = fopen(fileName,"r");
    short counter = 0;
    char chr = getc(ptr);

    while (chr != EOF)
    {
        if (chr == '\n') { counter++; }
        chr = getc(ptr);
    }

    fclose(ptr);
    return counter;
}