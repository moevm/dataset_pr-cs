#include "put.h"
#include "struct.h"
#include "my_lib.h"
#include <stdio.h>
#include <stdlib.h>
struct text* put() {
    int max_sentence = SIZE;
    struct text *text = malloc(sizeof(struct text));
    text->sentence = malloc(sizeof(struct sentence) * max_sentence);
    if (!text->sentence) {
        printf("Error: не удалось распределить память.");
    }
    text->count_sentence = 0;
    char symbol;
    int index = 0;
    int max_index = SIZE;
    for (int i = 0; i <= max_index; i++){
        text->sentence[i].str = (char*) malloc(sizeof(char) * max_index);
        if (!text->sentence[i].str) {
            printf("Error: не удалось распределить память.");
        }
    }
    fflush(stdin);
    symbol = getchar();
    do {
        while (((symbol) != '\n')){
            if (text->count_sentence >= max_sentence) {
                max_sentence *= SIZE;
                text->sentence = realloc(text->sentence, max_sentence * sizeof(struct sentence));
                if (!text->sentence) {
                    printf("Error: не удалось перераспределить память.");
                    exit(EXIT_FAILURE);
                }
                for (int i = max_sentence / SIZE; i < max_sentence; i++) {
                    text->sentence[i].str = (char*) malloc(sizeof(char)*max_index);
                    if (!text->sentence[i].str) {
                        printf("Error: не удалось распределить память.");
                    }
                }
            }

            if (index >= max_index) {
                max_index *= SIZE;
                text->sentence[text->count_sentence].str = realloc(text->sentence[text->count_sentence].str, max_index * sizeof(char));
                if (!text->sentence[text->count_sentence].str) {
                    printf("Error: не удалось перераспределить память.");
                    exit(EXIT_FAILURE);
                }
            }

            if (symbol == ' ' && index == 0) {
                symbol = getchar();
                continue;
            }

            if (symbol != '.') {
                text->sentence[text->count_sentence].str[index++] = symbol;
            }

            if (symbol == '.') {
                text->sentence[text->count_sentence].str[index++] = symbol;
                text->sentence[text->count_sentence].str[index] = '\0';
                text->sentence[text->count_sentence].print = 1;
                if (del_repeat(text, &text->sentence[text->count_sentence]) == 0) {
                    free(text->sentence[text->count_sentence].str);
                    text->sentence[text->count_sentence].str = (char*) malloc(sizeof(char)*max_index);
                    if (!text->sentence[text->count_sentence].str) {
                        printf("Error: не удалось перераспределить память.");
                        exit(EXIT_FAILURE);
                    }
                    index = 0;
                    max_index = SIZE;
                }
                else {
                    text->count_sentence++;
                    index = 0;
                    max_index = SIZE;
                }
            }

            symbol = getchar();
        }
        if ((symbol = getchar())!='\n' && index != 0) {
            text->sentence[text->count_sentence].str[index++] = '\n';
        }
    } while(symbol!='\n');
    if (index > 0) {
        text->sentence[text->count_sentence].str[index++] = '.';
        text->sentence[text->count_sentence].str[index] = '\0';
        text->sentence[text->count_sentence].print = 1;
        if (del_repeat(text, &text->sentence[text->count_sentence]) == 0) {
            free(text->sentence[text->count_sentence].str);
        }
        else {
            text->count_sentence++;
        }
    }
    if (text->count_sentence == 0) {
        printf("Error: пустой текст.");
        return 0;
    }
    return text;
}