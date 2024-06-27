#include <stdio.h>
#include <stdlib.h>
#include "structures.h"


void print_text(Text* text)
{
    for (size_t i = 0; i < text->size; i++)
        printf("%s\n", text->sentence[i].chars);
}


void free_memory(Text* text)
{
    for (size_t i = 0; i < text->size; i++)
        free(text->sentence[i].chars);
    free(text->sentence);
}
