#pragma once

typedef struct
{
    char *sentence;
} Sentence;

typedef struct
{
    Sentence *sentences;
    int sentence_count;
} Text;

void trim(Sentence sentence);
Text read_text(); 