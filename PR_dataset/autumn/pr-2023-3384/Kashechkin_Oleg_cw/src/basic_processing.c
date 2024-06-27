#include <stdio.h>
#include <stdlib.h>
#include "basic_processing.h"
#include "read_text.h"

void basic_processing(Text text)
{
    for (int i = 0; i < text.sentence_count; i++)
    {
        printf("%s\n", text.sentences[i].sentence);
    }
}