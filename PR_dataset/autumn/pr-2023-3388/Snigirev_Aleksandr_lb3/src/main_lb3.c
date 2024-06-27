#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<locale.h>
#define BASE_SIZE 100
#define DRAGON "Dragon flew away!"
#define SENTENCE_END '\0'

int checking_sign(char* sentense)
{
    int len_sentense = strlen(sentense);
    int correct = 0;
    if (sentense[len_sentense - 1] == '?')
    {
        correct = 1;
    }
    return correct;
}
void output(char* sentense, int start_number, int finish_number)
{
    printf("%s\n", sentense);
    printf("Количество предложений до %d и количество предложений после %d", start_number, finish_number);
}
void change_function() {
    int size = BASE_SIZE;
    char* sentense = (char*)malloc(size * sizeof(char));
    int index = 0;
    int start_number = 0, finish_number = 0;
    char symbol;
    while (strcmp(sentense, DRAGON))
    {
        symbol = getchar();
        if ((index == 0) && ((symbol == '\t') || (symbol == ' ')))
            continue;
        if (index == size - 2)
        {
            size += BASE_SIZE;
            sentense = (char*)realloc(sentense, size * sizeof(char));
        }
        sentense[index] = symbol;
        index++;
        if ((symbol == '.') || (symbol == ';'))
        {
            sentense[index] = SENTENCE_END;
            printf("%s\n", sentense);
            free(sentense);
            sentense = (char*)calloc(size, sizeof(char));
            start_number++;
            finish_number++;
            index = 0;
        }
        int correct_sentense = checking_sign(sentense);
        if (correct_sentense == 1)
        {
            start_number++;
            index = 0;
            free(sentense);
            sentense = (char*)calloc(size, sizeof(char));
        }
    }
    output(sentense, start_number, finish_number);
    free(sentense);
}

int main() {
    change_function();
    return 0;
}
