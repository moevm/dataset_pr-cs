#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "read_text.h"
#include "replace_special_symbols.h"

void replace_special_symbols(Text text)
{
    for (int i = 0; i < text.sentence_count; i++)
    {
        for (int j = 0; j < strlen(text.sentences[i].sentence); j++)
        {
            if (!isalpha(text.sentences[i].sentence[j]) && !isdigit(text.sentences[i].sentence[j]) && text.sentences[i].sentence[j] != ' ')
            {
                printf(">special symbol<");
            }
            else
            {
                printf("%c", text.sentences[i].sentence[j]);
            }
        }
        putchar('\n');
    }
}