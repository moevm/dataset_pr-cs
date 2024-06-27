#include <stdio.h>  // io-functions
#include <stdlib.h> // for memory
#include <string.h> // strcmp
#include <ctype.h>  // isupper

// проверка на выделенную память
#define checkPtr(ptr, message) ({ if (ptr == NULL) { fprintf(stderr, message); free(ptr); return 1; } })

#define stop_symbols_len 3      // кол-во знаков конца предложения
#define ignore_symbols_len 2    // кол-во знаков которые нужно пропустить
#define max_uppercase_symbols 1 // кол-во заглавных символов в 1 предложении

int checkInArray(char symbol, char *array, size_t array_len);

int main()
{
    char stop_symbols[stop_symbols_len] = {'.', ';', '?'};
    char ignore_symbols[ignore_symbols_len] = {'\t', '\n'};
    char *end_sentence = "Dragon flew away!";

    size_t last_sentence_len = 0;
    char *last_sentence = calloc(last_sentence_len + 1, sizeof(char));
    checkPtr(last_sentence, "calloc() failed: insufficient memory!\n");

    size_t upper_symbols = 0;
    size_t sentence_in = 0;
    size_t sentence_out = 0;

    char symbol;
    while (1)
    {
        symbol = getchar();
        if (checkInArray(symbol, ignore_symbols, ignore_symbols_len) || (last_sentence_len == 0 && symbol == ' '))
            continue;

        if (isupper(symbol))
            upper_symbols++;

        last_sentence = realloc(last_sentence, (last_sentence_len + 1) * sizeof(char));
        checkPtr(last_sentence, "realloc() failed: insufficient memory!\n");
        last_sentence[last_sentence_len] = symbol;
        last_sentence_len++;

        if (checkInArray(symbol, stop_symbols, stop_symbols_len) || !strcmp(last_sentence, end_sentence))
        {
            if (strcmp(last_sentence, end_sentence))
                sentence_in++;

            if (upper_symbols <= max_uppercase_symbols)
            {
                last_sentence = realloc(last_sentence, (last_sentence_len + 1) * sizeof(char));
                checkPtr(last_sentence, "realloc() failed: insufficient memory!\n");
                last_sentence[last_sentence_len] = '\0';

                puts(last_sentence);

                if (strcmp(last_sentence, end_sentence))
                    sentence_out++;
            }

            if (!strcmp(last_sentence, end_sentence))
                break;

            memset(last_sentence, 0, last_sentence_len + 1);
            last_sentence_len = 0;
            last_sentence = realloc(last_sentence, (last_sentence_len + 1) * sizeof(char));
            checkPtr(last_sentence, "realloc() failed: insufficient memory!\n");
            upper_symbols = 0;
        }
    }

    printf("Количество предложений до %d и количество предложений после %d", sentence_in, sentence_out);

    // Очищение памяти
    free(last_sentence);
    return 0;
}

int checkInArray(char symbol, char *array, size_t array_len)
{
    for (size_t i = 0; i < array_len; ++i)
        if (array[i] == symbol)
            return 1;

    return 0;
}