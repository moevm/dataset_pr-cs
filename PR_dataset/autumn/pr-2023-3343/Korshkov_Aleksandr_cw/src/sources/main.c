#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include <string.h>
#include <ctype.h>

#include "../include/init_proc_text.h"
#include "../include/proc_time.h"
#include "../include/delete_first_word.h"
#include "../include/sort_by_lowercase.h"
#include "../include/delete_equal_words.h"
#include "../include/create_new_sentences.h"

int main()
{
    setlocale(LC_ALL, "");
    puts("Course work for option 4.11, created by Aleksandr Korshkov."); // начальная строчка

    int mode = -1;
    int count = -1;
    
    scanf("%d", &mode);
    switch (mode)
    {
    case 0: // базовый вывод текста
    {
        char *text = inputText();
        char **init_sentences = splitSentences(text, &count);
        char **sentences = deleteRepeatSentences(init_sentences, &count);

        printSentences(sentences, &count);

        free(text);
        free(init_sentences);
        free(sentences);
        break;
    }

    case 1: // поиск и подсчёт времени из строк вида "<sec>sec"
    {
        char *text = inputText();
        char **init_sentences = splitSentences(text, &count);
        char **sentences = deleteRepeatSentences(init_sentences, &count);

        secondsToTime(sentences, &count);

        free(text);
        free(init_sentences);
        free(sentences);
        break;
    }

    case 2: // удаление первого слова из предложения
    {
        char *text = inputText();
        char **init_sentences = splitSentences(text, &count);
        char **sentences = deleteRepeatSentences(init_sentences, &count);

        char **res = deleteFirstWord(sentences, &count);
        printSentences(res, &count);

        free(text);
        free(init_sentences);
        free(sentences);
        free(res);
        break;
    }
    case 3: // удаляет предложения, если их слова имеют одинаковую длину
    {
        char *text = inputText();
        char **init_sentences = splitSentences(text, &count);
        char **sentences = deleteRepeatSentences(init_sentences, &count);

        char **res = deleteEqualLenWords(sentences, &count);
        printSentences(res, &count);

        free(text);
        free(init_sentences);
        free(sentences);
        free(res);
        break;
    }
    case 4:  // сортирует предложения по ументшению кол-ва строчных букв
    {
        char *text = inputText();
        char **init_sentences = splitSentences(text, &count);
        char **sentences = deleteRepeatSentences(init_sentences, &count);

        sortSentences(sentences, &count);
        printSentences(sentences, &count);

        free(text);
        free(init_sentences);
        free(sentences);
        break;
    }

    case 5: //Вывод строчки
        printHelp();
        break;

    case 9:
    {
        getchar();
        char Der[101];
        fgets(Der, 101, stdin);

        if (Der[strlen(Der) - 1] == '\n') {
            Der[strlen(Der) - 1] = '\0';
        }

        char *text = inputText();
        char **init_sentences = splitSentences(text, &count);
        char **sentences = deleteRepeatSentences(init_sentences, &count);

        char** res = create_new_sentences(sentences, &count, Der);
        printSentences(res, &count);

        break;
        
    }
    default: // Не введено число от 0 до 5
        fprintf(stderr, "Error: Invalid command number value\n");
        break;
    }
    return 0;
}
