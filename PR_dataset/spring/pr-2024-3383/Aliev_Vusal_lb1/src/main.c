#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>
#define N 20;

int main(void){

    char* regexString = "([a-zA-Z0-9_]+)@([a-zA-Z0-9_-]+): ?~ ?# (.+)";
    size_t maxGroup = 4;

    regex_t regexComplited;
    regmatch_t groupArr[maxGroup];

    if (regcomp(&regexComplited, regexString, REG_EXTENDED)){ 
        puts("Ошибка при компиляции строки!");
        return 0;
    }

    size_t sizeText = N;
    size_t sizeSent = N;
    char** text = malloc(sizeof(char*) * sizeText);

    int count_sent = 0;

    for (int i = 0;; i++){

        text[i] = malloc(sizeof(char) * sizeSent);
        char symbol = getchar();

        int M = 0;

        for (;(symbol != '\n') && (symbol != EOF) ;M++){

            if (M == sizeSent - 1){
                sizeSent += N;
                text[i] = realloc(text[i],sizeof(char)* sizeSent);
            }

            text[i][M] = symbol;
            symbol = getchar();
        }

        text[i][M] = '\0';
        count_sent++;

        if (i == sizeText - 1){
            sizeText += N;
            text = realloc(text,sizeof(char*) * sizeText);
        }

        if (strcmp(text[i], "Fin.") == 0){
            break;
        }
    }

    for (int i = 0; i < count_sent;i++){
        if (regexec(&regexComplited, text[i], maxGroup, groupArr, 0) == 0){
            for (int j = groupArr[1].rm_so; j < groupArr[1].rm_eo;j++){
                printf("%c", text[i][j]);
            }
            printf(" - ");
            for (int k = groupArr[3].rm_so; k < groupArr[3].rm_eo;k++){
                printf("%c", text[i][k]);
            }
            printf("\n");
        }
        
    }

    for (int i = 0; i< count_sent; i++) {
        free(text[i]);
    }

    regfree(&regexComplited);
    free(text);
    return 0;
}