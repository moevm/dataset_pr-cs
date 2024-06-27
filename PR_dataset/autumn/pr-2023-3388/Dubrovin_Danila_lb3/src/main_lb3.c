#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INPUT_SIZE 1000000 // Длина буфера
#define SENTENCES_MAX_COUNT 1000 // Максимальное количество предложений, доступное для считывания
#define WORDS_MAX_COUNT 50 // Максимальное количество слов в предложении, доступное для считывания

/*Проверка строки на число*/
int is_number(const char *str)
{
    if (str == NULL || *str == '\0') 
    {
        return 0;
    }
    char *endptr;
    strtol(str, &endptr, 10);

    return (*endptr == '\0');
}

/*Проверка предложения на удовлетворение условиям*/
int check_sentence(char *sentence)
{
    int ans = 1; // вывод функции
    char **words = malloc(sizeof(char*) * WORDS_MAX_COUNT);
    int word_count = 0;
    char *token = strtok(sentence, " .?;"); // Разбиваем предложение на слова
    while (token != NULL && word_count < WORDS_MAX_COUNT) 
    {
        words[word_count] = strdup(token);
        word_count++;
        token = strtok(NULL, " .?;");
    }
    for (int i = 0; i < word_count; i++) // Поиск неудовлетворяющих условиям предложений
    {
        if (!(is_number(words[i])))
        {
            for (int j = 0; j < strlen(words[i]); j++) 
            {
                if (isdigit(words[i][j]) && (j != 0 && j != strlen(words[i]) - 1))
                {
                    ans = 0;
                    break;
                }
            }
        }
        free(words[i]);
    }
    free(words);
    return ans;
}

/*Поиск и вывод предложений*/
void find_and_print_sentences(char *input)
{
    char **sentences = malloc(sizeof(char*) * SENTENCES_MAX_COUNT); // Массив для хранения ссылок на предложения
    int sent_count = 0; // Количество считанных предложений
    int sent_old = 0; // Количество предложений до работы программы
    int cursor = 0; // Текущая позиция в input, из которой считывается предложение

    for (int i = 0; input[i]; i++) 
    {
        if ((input[i] == '.') || (input[i] == '?') || (input[i] == ';') || (input[i] == '!' && input[i + 1] == '\n')) 
        {
            sentences[sent_count] = malloc(sizeof(char) * (i - cursor + 2));
            for (int j = 0; j < (i - cursor + 1); j++) 
            {
                sentences[sent_count][j] = input[cursor + j];
            }
            sentences[sent_count][i - cursor + 1] = '\0';
            if (check_sentence(strdup(sentences[sent_count])))// Если предложение удовлетворяет условиям, то оставляем его в массиве
            {
                sent_count++;
            }
            sent_old++;
            cursor = i + 2;
        }
    }

    for (int i = 0; i < sent_count; i++) 
    {
        printf("%s\n", sentences[i]);
        free(sentences[i]);
    }
    printf("Количество предложений до %d и количество предложений после %d\n", sent_old - 1, sent_count - 1);
    free(sentences);
}

int main() 
{
    char *input = malloc(INPUT_SIZE); // Буфер для считывания строки
    fgets(input, INPUT_SIZE, stdin); // Считывание строки
    find_and_print_sentences(input);
    free(input);

    return 0;
}
