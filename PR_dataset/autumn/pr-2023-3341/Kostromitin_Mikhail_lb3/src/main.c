#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 150
#define ENDOFSTRING '\0'

char* input();
char* signsOfEnd(char* text, int* lenOfText);
char** sentencesFunc(char* text);
char** formSentencesFunc(char** sentences, int sizeOfSentences, int* sizeOfFormSentences, char* signs_of_end);
void output(char** formSentences, int sizeOfFormSentences);
void freeMem(char** text, char** signs, char*** sentences, int sizeSentences, char*** formSentences, int sizeFormSentences);

int main()
{
    char* text = input();

    int numberOfSentences = 0;
    char* signs = signsOfEnd(text, &numberOfSentences);

    char** sentences = sentencesFunc(text);

    int numberOfFormSentences = 0;
    char** formSentences = formSentencesFunc(sentences, numberOfSentences, &numberOfFormSentences, signs);

    output(formSentences, numberOfFormSentences);

    freeMem(&text, &signs, &sentences, numberOfSentences + 1, &formSentences, numberOfFormSentences + 1);

    return 0;
}


char* input()
{
    int current_block = BLOCK_SIZE;
    char* text = (char*)malloc(current_block);
    int indx = 0;
    char read = getchar();

    while(read != '\n' && read != ENDOFSTRING && read != EOF)
    {
        if ((indx + 2) >= current_block)
        {
            char* buf = (char*)realloc(text, current_block + BLOCK_SIZE);
            text = buf;
            current_block += BLOCK_SIZE;
        }
        text[indx++] = read;
        read = getchar();
    }
    text[indx] = ENDOFSTRING;

    return text;
}


char* signsOfEnd(char* text, int* lenOfText)
{
    int current_block = BLOCK_SIZE;
    char* signs = (char*)malloc(current_block);
    int index = 0;
    while(text[index] != ENDOFSTRING)
    {
        if (text[index] == ';' || text[index] == '.' || text[index] == '?')
        {
            if ((*lenOfText) >= current_block)
            {
                char* buf = (char*)realloc(signs, current_block + BLOCK_SIZE);
                signs = buf;
                current_block += BLOCK_SIZE;
            }
            signs[*lenOfText] = text[index];
            (*lenOfText)++;
        }
        index++;
    }
    signs[*lenOfText] = ENDOFSTRING;

    return signs;
}


char** sentencesFunc(char* text)
{
    int current_block = BLOCK_SIZE;
    char** sentences = (char**)malloc(sizeof(char*) * current_block);
    int size = 0;
    char* bufStr = strtok(text, ";.?");
    sentences[size] = (char*)malloc(strlen(bufStr) + 1);
    strcpy(sentences[size], bufStr);
    size++;

    while ((bufStr = strtok(NULL, ".;?")) != NULL)
    {
        if ((size + 2) >= current_block)
        {
            current_block += BLOCK_SIZE;
            char** buf = (char**)realloc(sentences, sizeof(char*) * current_block);
            sentences = buf;
        }
        sentences[size] = (char*)malloc(strlen(bufStr) + 1);
        strcpy(sentences[size], bufStr);

        size++;
    }

    return sentences;
}


char** formSentencesFunc(char** sentences, int sizeOfSentences, int* sizeOfFormSentences, char* signs_of_end)
{
    char** formSentences = (char**)malloc(sizeof(char*) * (sizeOfSentences + 1));
    
    for (int i = 0; i <= sizeOfSentences; i++)
    {
        if (strstr(sentences[i], "7") == NULL)
        {
            formSentences[*sizeOfFormSentences] = (char*)calloc(strlen(sentences[i]) + 3, sizeof(char));
            strcpy(formSentences[*sizeOfFormSentences], sentences[i]);
            formSentences[*sizeOfFormSentences] += (*sizeOfFormSentences) ? (1):(0);
            formSentences[*sizeOfFormSentences][strlen(formSentences[*sizeOfFormSentences])] = (i < sizeOfSentences) ? (signs_of_end[i]):(ENDOFSTRING);
            formSentences[*sizeOfFormSentences][strlen(formSentences[*sizeOfFormSentences]) + 1] = ENDOFSTRING;
            (*sizeOfFormSentences)++;
        }
    }
    formSentences[*sizeOfFormSentences] = calloc(strlen("Количество предложений до %d и количество предложений после %d") + 1, sizeof(char));
    sprintf(formSentences[*sizeOfFormSentences], "Количество предложений до %d и количество предложений после %d", sizeOfSentences, ((*sizeOfFormSentences) - 1));

    return formSentences;
}


void output(char** formSentences, int m)
{
    for (int i = 0; i < m; i++)
    {
        printf("%s\n", formSentences[i]);
    }
    printf("%s", formSentences[m]);
}


void freeMem(char** text, char** signs, char*** sentences, int sizeSentences, char*** formSentences, int sizeFormSentences)
{
    free(*text);
    free(*signs);
    for (int i = 0; i < sizeSentences; i++)
    {
        free((*sentences)[i]);
    }
    free(*sentences);
    free((*formSentences)[0]);
    for (int i = 1; i < (sizeFormSentences - 1); i++)
    {
        free(((*formSentences)[i]) - 1);
    }
    free(*formSentences);
}
