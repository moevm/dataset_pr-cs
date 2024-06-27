#include "Input.h"
#include "Common.h"

char* ReadSentence(int* sentence_len)
{
    char* sentence = (char*)malloc(sizeof(char) * MEM_STEP);
    if (sentence == NULL)
        return NULL;
    int memory = MEM_STEP;
    char symbol;
    int index = 0;
    int new_lines = 0;
    while ((symbol = getchar()) != EOF)
    {
        if (symbol == '\n')
        {
            new_lines++;
            if (new_lines == 2)
            {
                free(sentence);
                return NULL;
            }
            continue;
        }
        new_lines = 0;
        if (symbol == '\n' || isspace(symbol))
        {
            if (index == 0)
                continue;
        }
        sentence[index] = symbol;
        index++;
        if (index == memory - 1)
        {
            memory += MEM_STEP;
            char* temp = (char*)realloc(sentence, sizeof(char) * memory);
            if (temp == NULL)
            {
                free(sentence);
                return NULL;
            }
            sentence = temp;
        }
        if (symbol == '.')
            break;
    }
    sentence[index] = '\0';
    *sentence_len = index;
    return sentence;
}

char** ReadText(int* sentences_count)
{
    int memory = MEM_STEP;
    char** text = (char**)malloc(sizeof(char*) * memory);
    if (text == NULL)
        return NULL;
    int count = 0;
    char* sentence;
    int sentence_len = 0;
    while ((sentence = ReadSentence(&sentence_len)) != NULL)
    {
        int IsDup = 0;
        if (count != 0)
        {
            for (int i = 0; i < count; i++)
            {
                if (strcasecmp(sentence, text[i]) == 0)
                {
                    free(sentence);
                    IsDup = 1;
                    break;
                }
            }
        }
        if (IsDup == 1)
            continue;
        text[count] = sentence;
        count++;
        if (count == memory) {
            memory += MEM_STEP;
            text = (char**)realloc(text, sizeof(char*) * memory);
            if (text == NULL)
                return NULL;
        }
    }
    *sentences_count = count;
    return text;
}
