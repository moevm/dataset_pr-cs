#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "structures.h"
#include "countnums.h"


void print_nums(size_t counts[])
{
    size_t count = 0;
    for (size_t i = 0; i < 10; i++)
    {
        if (counts[i] > 0) 
            printf("Num - %zu, count - %zu\n", i, counts[i]);
        else
            count++;
    }
    if (count == 10)
        printf("There are no numbers in this text.\n");
}


void count_digits(Text *text)
{
    size_t counts[10] = {0};
    for (size_t i = 0; i < text->size; i++)
    {
        Sentence *sentence = &text->sentence[i];
        for (size_t j = 0; j < sentence->size; j++)
        {
            if (isdigit(sentence->chars[j]))
            {
                size_t digit = sentence->chars[j] - '0'; // ASCII '0' = 48; ASCII '1' = 49; '1' - '0' = 1
                counts[digit]++; 
            }
        }
    }
    print_nums(counts);
}
