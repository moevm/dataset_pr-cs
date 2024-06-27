#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(){
    char **text;
    int count = 3, element = 0, sentence = 0;
    text = (char**)malloc(sizeof(char*));
    text[sentence] = (char*)malloc(2*sizeof(char));
    char symbol;
    int flag = 1;
    symbol = getchar();
    while (flag) {
        if (symbol == '.' || symbol == ';' || symbol == '?' || symbol == '!') {
            text[sentence][element] = symbol;
            text[sentence][element+1] = '\0';
            if (symbol == '!') {
                flag = 0;
                break;
            }
            symbol = getchar(); //reading space
            sentence += 1;
            count = 3;
            element = 0;
            text = (char**)realloc(text, (sentence+1)*sizeof(char*));
            text[sentence] = (char*)malloc(sizeof(char));
        }
        else {
            text[sentence][element] = symbol;
            text[sentence] = (char*)realloc(text[sentence], count*sizeof(char));
            element++;
            count++;
        }
        symbol = getchar();
    }
    int sentence_number_before, sentence_number_after = 0;
    int big_letters = 0;
    sentence_number_before = sentence;
    for (int i = 0; i <= sentence; i++) {
        for (int j = 0; j < strlen(text[i]); j++) {
            if (isalpha(text[i][j]) && isupper(text[i][j])) {
                big_letters++;
            }
        }
        if (big_letters <= 1) { 
            printf("%s\n", text[i]);
            sentence_number_after++;
        }
        big_letters = 0;
    }
    for (int i = 0; i <= sentence; i++) {
        free(text[i]);
    }
    free(text);
    printf("Количество предложений до %d и количество предложений после %d", sentence_number_before, sentence_number_after-1);
    return 0;
}