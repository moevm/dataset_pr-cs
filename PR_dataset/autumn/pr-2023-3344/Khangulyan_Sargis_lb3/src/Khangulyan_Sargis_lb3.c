#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* tab_delete(char* sentence) {
    if ((sentence[0] == ' ') || (sentence[0]) == '\t') {
        memmove(sentence, sentence + 1, strlen(sentence));
    }
    return sentence;
}

int main(){
    char** input_text = (char**)malloc(sizeof(char*));
    int input_text_count = 0;
    int changed_text_count = 0;

    while (1) {
        char* sentence = (char*)malloc(sizeof(char));
        char symbol = ' ';
        int sentence_count = 0;
        int check_1 = 0, check_2 = 0, check_3 = 0;
        int check_sentence = 1;

        while (symbol != '.' && symbol != ';' && symbol != '?' && symbol != '!') {
            symbol = getchar();
            if (symbol == '\n') {
                symbol = ' ';
            }

            if (symbol == ' ') {
                check_1 = 0;
                check_2 = 0;
                check_3 = 0;
            }
            if (isalpha(symbol)) {
                check_1 = 1;
            }
            if (isdigit(symbol) && check_1 == 1) {
                check_2 = 1;
            }
            if (isalpha(symbol) && check_1 == 1 && check_2 == 1) {
                check_3 = 1;
            }

            if (check_1 == 1 && check_2 == 1 && check_3 == 1) {
                check_sentence = 0;
            }

            sentence[sentence_count++] = symbol;
            sentence = realloc(sentence, sizeof(char)*(sentence_count + 1));
        }

        sentence[sentence_count] = '\0';
        tab_delete(sentence);
        input_text_count++;

        if (check_sentence) {
            input_text[changed_text_count++] = sentence;
            input_text = realloc(input_text, sizeof(char*)*(changed_text_count + 1));
        }

        if (strstr(sentence, "Dragon flew away!")) { 
            break;
        }
    }

    for (int i = 0; i < changed_text_count; i++){
        printf("%s\n", input_text[i]);
        free(input_text[i]);
    }
    free(input_text);

    printf("Количество предложений до %d и количество предложений после %d\n", input_text_count - 1, changed_text_count - 1);

    return 0;
}