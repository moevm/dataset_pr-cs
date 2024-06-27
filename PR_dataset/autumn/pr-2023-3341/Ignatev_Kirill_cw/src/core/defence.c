#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../header/defence.h"

char* getKeySentence(){
    char* word = NULL, c;
    int len=0;
    word= malloc(sizeof(char ));
    c=getchar();
    while ((c=getchar())!='\n'){
        word[len]=c;
        len++;
        word= realloc(word, len+1);
    }
    word[len]='\0';
    return word;
}

void defence(char** text, int* sentences_num, char* keysentence){
    if ((*sentences_num)%2!=0) {
        for (int i = 0; i < (*sentences_num) / 2 + 1; ++i) {
            printf("%s ", text[i]);
            printf("%s ", keysentence);
            printf("%s.\n", text[(*sentences_num - 1) - i]);
        }
    } else{
        for (int i = 0; i < (*sentences_num) / 2; ++i) {
            printf("%s ", text[i]);
            printf("%s ", keysentence);
            printf("%s.\n", text[(*sentences_num - 1) - i]);
        }
    }
}
