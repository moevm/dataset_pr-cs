#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "structures.h"
#include "input.h"

#define BLOCK_SIZE 20


Sentence input_sentence(size_t* end)
{
    char ch = '\0';
    size_t capacity = BLOCK_SIZE, size = 0;
    Sentence sentence;
    sentence.chars = malloc(capacity * sizeof(char));
    sentence.size = 0;
    while (ch != '.')
    {
        ch = (char)getchar();
        if (ch == '\n')
        {
            if (++(*end) == 2)
                break;
        }
        else
            *end = 0;
        if (isspace(ch) && size == 0)
            continue;
        sentence.chars[size++] = ch;
        if (size == capacity)
        {
            capacity += BLOCK_SIZE;
            sentence.chars = realloc(sentence.chars, capacity * sizeof(char));
            if (sentence.chars == NULL){
                fprintf(stderr, "Error: not enough memory");
                exit(0);
            }
        }
    }
    sentence.size = size;
    sentence.chars = realloc(sentence.chars, (size + 1) * sizeof(char));
    sentence.chars[size] = '\0';

    return sentence;
}


int cmpstr(char* a, char* b)
{
    size_t i = 0;
    while (a[i] != '\0' && b[i] != '\0')
    {
        if (tolower(a[i]) != tolower(b[i]))
            return 0;
        i++;
    }
    if ((a[i] == '\0') ^ (b[i] == '\0'))
        return 0;
    return 1;
}


Text input_text(void)
{
    size_t capacity = BLOCK_SIZE, size = 0, end = 0;
    Text text;
    text.sentence = (Sentence*)malloc(capacity * sizeof(Sentence));
    text.size = 0;
    while (end < 2)
    {
        Sentence tempsentence = input_sentence(&end);
        if (end == 2)
            break;
        size_t is_double = 0;
        for (size_t i = 0; i < size; i++)
            if (cmpstr(text.sentence[i].chars, tempsentence.chars) == 1)
            {
                is_double = 1;
                break;
            }
        if (is_double)
            continue;
        text.sentence[size++] = tempsentence;
        if (size == capacity){
            capacity += BLOCK_SIZE;
            text.sentence = (Sentence*)realloc(text.sentence, capacity * sizeof(Sentence));
            if (text.sentence == NULL){
                fprintf(stderr, "Error: not enough memory");
                exit(0);
            }
        }
    }
    text.size = size;

    return text;
}
