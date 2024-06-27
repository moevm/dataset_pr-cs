#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../include/init_proc_text.h"

char *strlower(char *sentence) // приведение предложения к строчному виду
{
    char *res = (char *)malloc((strlen(sentence) + 1) * sizeof(char));
    for (int i = 0; i < strlen(sentence) + 1; i++)
        res[i] = tolower(sentence[i]);
    return res;
}

void printHelp() // вывод справки
{
    printf("0) Вывод текста после первичной обязательной обработки (если предусмотрена заданием данного уровня сложности)\n"
           "1) Найти все предложения в которых есть слова вида “<число>sec>” (“23sec”) задающие количество секунд.\nДля каждого такого предложения посчитать количество секунд и вывести количество полученных часов, минут и секунд в виде строки “hour:min:sec”.\n"
           "2) В каждом предложении удалить первое слово. Если в предложении не останется слов, то его надо удалить.\n"
           "3) Удалить все предложения у которых длины всех слов одинаковые.\n"
           "4) Отсортировать предложения по уменьшению количества строчных букв в нем.\n"
           "5) Вывод справки о функциях, которые реализует программа.\n");
}

char **splitSentences(char *text, int *count_sent) // деление текста на предложения
{
    char **sentences = malloc(sizeof(char *));
    int count = 0;

    char *sent_tok = strtok(text, ".");
    while (sent_tok != NULL)
    {
        while (isspace(sent_tok[0]))
            memmove(&sent_tok[0], &sent_tok[1], strlen(sent_tok));
        char *sentence = malloc((strlen(sent_tok) + 2) * sizeof(char));
        strcpy(sentence, sent_tok);
        sentence[strlen(sent_tok)] = '.';
        sentence[strlen(sent_tok) + 1] = '\0';
        sentences[count++] = sentence;
        sentences = realloc(sentences, (count + 1) * sizeof(char *));
        sent_tok = strtok(NULL, ".");
    }
    *count_sent = count;
    return sentences;
}
char **deleteRepeatSentences(char **init_sentences, int *count) { // удаление повторяющихся предложений
    char **sentences = (char **)malloc(sizeof(char *));
    int *del_idx = (int *)malloc(sizeof(int));
    int temp1 = 0, temp2 = 0;

    for (int i1 = 0; i1 < *count - 1; i1++)
    {
        char *first_sentence = strlower(init_sentences[i1]);
        for (int i2 = i1 + 1; i2 < *count; i2++)
        {
            char *second_sentence = strlower(init_sentences[i2]);
            if (strcmp(first_sentence, second_sentence) == 0)
            {
                del_idx[temp1++] = i2;
                del_idx = realloc(del_idx, (temp1 + 1) * sizeof(int));
            }
            free(second_sentence);
        }
        free(first_sentence);
    }

    for (int s = 0; s < *count; s++)
    {
        int flag = 0;
        for (int check = 0; check < temp1; check++)
        {
            if (del_idx[check] == s)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            sentences[temp2++] = init_sentences[s]; /// temp1 and s so that there are no "spaces" in compared_text
            sentences = realloc(sentences, (temp2 + 1) * sizeof(char *));
        }
    }
    free(del_idx);
    *count = temp2;
    return sentences;
}
void printSentences(char **sentences, int *count) { // вывод предложений в консоль и очистка памяти
    for (int i = 0; i < *count; i++)
    {
        puts(sentences[i]);
        free(sentences[i]);
    }
}

char *inputText() // ввод текста
{
    char symbol;
    char *text = malloc(10 * sizeof(char));
    int count = 0;

    while (strstr(text, "\n\n") == NULL)
    {
        symbol = getchar();
        text[count++] = symbol;
        text = realloc(text, sizeof(char) * (count + 2));
    }
    text[count - 2] = '\0';
    return text;
}
