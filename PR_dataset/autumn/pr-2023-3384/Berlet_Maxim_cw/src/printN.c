#include "printN.h"
#include <stdlib.h>
#include "mfuncs.h"
#include <stdio.h>
#include "mclean.h"
#include <string.h>
#define BLU_COL "\e[0;34m"

void print0(char** sentences, int counter){
    for(int a = 0; a < counter; a++){
        printf("%s\n", sentences[a]);
    }    
}

void print2(char** sentences, int counter){
    //Заменить последовательность подряд идущих букв
    for(int j = 0; j < counter; j++){
        replace_repeated_let(sentences[j], counter);
        printf("%s\n", sentences[j]);
    }
}

void print3(char** sentences, int counter){
    //Удалить все предложения в которых количество слов кратно трем.
    char** newstrs = (char**)malloc(sizeof(char*)*counter);
    newstrs = del_sent(sentences, &counter);
    newstrs = realloc(newstrs, sizeof(char*)*counter);
    for(int i = 0; i < counter; i++){
        printf("%s\n", newstrs[i]);
    }
    clean_memory(newstrs, counter);
}

void print4(char** sentences, int counter){
    //Отсортировать предложения по уменьшению суммарной длины первого и последнего слова.
    qsort(sentences, counter, sizeof(char*), comparator);
    for(int q = 0; q < counter; q++){
        printf("%s\n", sentences[q]);
    }
}

void colors(char** sentences, int* counter){
    const char *blueKeyword = "define BLUE";
    int cnt = (*counter);
    for(int i = 0; i < cnt; i++){
        char* ptr = strstr(sentences[i], blueKeyword);
        if(ptr){
            ptr += strlen(blueKeyword)+1;
            printf("%.*s"BLU_COL, (int)(ptr - sentences[i]), sentences[i]);
            printf("%s\n", ptr);
        }
        else{
            printf("%s\n", sentences[i]);
        }
    }
}
