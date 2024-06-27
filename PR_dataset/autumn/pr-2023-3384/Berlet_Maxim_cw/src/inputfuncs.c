#include "inputfuncs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#define BLOCK_SIZE 10

char** strs_input(int* counter){
    char* str = (char*)malloc(BLOCK_SIZE);
    char** sentances = (char**)malloc(sizeof(char*)*BLOCK_SIZE);
    int strcapacity = BLOCK_SIZE;
    int strscapacity = BLOCK_SIZE;
    int idx = 0;
    int strsidx = 0;
    if(str == NULL){
        puts("Error: <Memory allocation failed>");
        exit(1);
    }
    if(sentances == NULL){
        puts("Error: <Memory allocation failed>");
        exit(1);
    }
    while(1){
        if(strcapacity == idx){
            str = (char*)realloc(str, strcapacity+BLOCK_SIZE);
            strcapacity += BLOCK_SIZE;
            if(str == NULL){
                puts("Error: <Memory reallocation failed>");
                exit(1);
            }
        }
        if(strscapacity == (strsidx)){
            sentances = (char**)realloc(sentances, sizeof(char*)*(strscapacity+BLOCK_SIZE));
            strscapacity += BLOCK_SIZE;
            if(sentances == NULL){
                puts("Error: <Memory reallocation failed>");
                exit(1);
            }
        }

        char c = getchar();
        str[idx] = c;
        if(str[idx] == '.'){
            if(str[0] == '\n'){
                for(int q = 0; q<idx; q++){
                    str[q] = str[q+1];
                }
                str[idx] = '\0';
            }
            sentances[(strsidx)] = (char*)malloc(idx+2);
            memcpy(sentances[(strsidx)], str, idx + 1);
            sentances[strsidx][idx+1] = '\0';
            strsidx++;
            free(str);
            str = (char*)malloc(BLOCK_SIZE);
            idx = 0;
            strcapacity = BLOCK_SIZE;
            continue;
        }
        if (idx > 0 && str[idx] == '\n' && str[idx - 1] == '\n') {
            if(idx > 1 ){
                sentances[(strsidx)] = (char*)malloc(idx+1);
                memcpy(sentances[(strsidx)], str, idx);
                sentances[strsidx][idx] = '\0';
                strsidx++;
            }
            free(str);
            *counter = strsidx;
            return sentances;
        }
        if (idx != 0 || (str[idx] != ' ' && str[idx] != '\t'))
            idx++;
    }
}

int is_sentence_repeated(char* sentence1, char* sentence2){
    if(strlen(sentence1) != strlen(sentence2)){
        return 0;
    }
    while (*sentence1 && (tolower(*sentence1) == tolower(*sentence2)))
    {
        sentence1++;
        sentence2++;
    }
    return !(*sentence1 - *sentence2);
}

void strs_preprocessing(char** sentences, int* sentencesnum){
    int shift = 0;
    int sentnum = (*sentencesnum);
    for (int i = 0; i + shift < sentnum; i++) {
        sentences[i] = sentences[i + shift];
        for (long int j = i - 1; j >= 0; j--) {
            if (is_sentence_repeated(sentences[i], sentences[j])) {
                shift++;
                i--;
                break;
            }
        }
    }
    sentnum -= shift;
    *sentencesnum = sentnum;
}