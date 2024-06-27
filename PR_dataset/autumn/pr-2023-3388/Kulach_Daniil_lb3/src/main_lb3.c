#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPPERCASE_A 65
#define UPPERCASE_Z 90
#define NULL_TERMINATOR '\0'

void processInput() {
    char *text = NULL, symbol;
    int length_text = 0;
    int sentences_after_format = 0, sentences_before_format = 0;
    text = (char*) malloc(sizeof(char));
    int count = 0;
    int count_big = 0;

    while((symbol = getchar()) != '!') {
        if ((symbol != '.') && (symbol != ';') && (symbol!= '?') && (symbol!= '\n') && (symbol!= '\t')) {
            if (symbol >= UPPERCASE_A && symbol <= UPPERCASE_Z) {
                count_big ++;
            }
            text[length_text] = symbol;
            length_text++;
            text = (char*) realloc(text, length_text + 1);
            count++;
        } else {
            if (symbol == '.' || symbol == ';' || symbol == '?') {
                if (count_big >= 2) {
                    length_text = length_text - count;
                    sentences_before_format++;
                    count = 0;
                    symbol = getchar();
                    count_big = 0;
                } else {
                    count = 0;
                    text[length_text] = symbol;
                    length_text ++;
                    text = (char*) realloc(text, length_text + 1);
                    text[length_text] = '\n';
                    length_text ++;
                    getchar();
                    sentences_after_format++;
                    sentences_before_format++;
                    count_big = 0;
                }
            }
        }
    }

    text[length_text] = '!';
    length_text++;
    text = (char*) realloc(text, length_text + 1);
    text[length_text] = NULL_TERMINATOR;
    printf("%s\n", text);
    free(text);
    printf("Количество предложений до %d и количество предложений после %d",sentences_before_format ,sentences_after_format);
}

int main() {
    processInput();
    return 0;
}
