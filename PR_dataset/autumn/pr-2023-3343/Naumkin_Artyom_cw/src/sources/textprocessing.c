#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structures.h"
#include "textprocessing.h"


void flip_sentence(char* str)
{
    const char* splitters = " .,";
    size_t left = 0, right = strlen(str) - 1;
    while (left < right)
    {
        while (left < right && strchr(splitters, str[left]))
            left++;
        while (left < right && strchr(splitters, str[right]))
            right--;
        char temp = str[left];
        str[left++] = str[right];
        str[right--] = temp;
    }
}


void flip_all_text(Text* text)
{
    for (size_t i = 0; i < text->size; i++)
        flip_sentence(text->sentence[i].chars);
}


void remove_with_physics(Text* text)
{
    const char* word = "physics";
    for (size_t i = 0; i < text->size; i++)
    {
        if (strstr(text->sentence[i].chars, word) != NULL)
        {
            free(text->sentence[i].chars);
            for (size_t j = i; j < text->size - 1; j++)
                text->sentence[j] = text->sentence[j + 1];
            text->size--;
            i--;
        }
    }
}
