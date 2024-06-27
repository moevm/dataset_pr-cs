#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "mfuncs.h"

void replace_repeated_let(char* str, int counter){
    int len = strlen(str);
    char result[len];
    int count = 1;
    int resultIndex = 0; 

    for (int i = 1; i <= len; i++) {
        char current = toupper(str[i]);
        char prev = toupper(str[i - 1]);
        if(current == prev){
            count++;
        } 
        else{
            if(count > 1){
                resultIndex += snprintf(result + resultIndex, sizeof(result) - resultIndex, "%d", count);
                result[resultIndex++] = toupper(str[i - 1]);
                count = 1;
            }
            else{
                result[resultIndex++] = str[i - 1];
            }
        }
    }
    result[resultIndex] = '\0';
    strcpy(str, result);
}

char** del_sent(char** sentences, int* sentencesnum){
    char** res = (char**)malloc(sizeof(char*)*(*sentencesnum));
    if(res == NULL){
        puts("Error: <Memory allocation failed>");
        exit(1);
    }
    int sentnum = (*sentencesnum);
    int newsentnum = 0;
    for (int i = 0; i < sentnum; i++) {
        if(!is_mul_three(sentences[i])){
            res[newsentnum] = sentences[i];
            newsentnum++;
        }
        else{
            free(sentences[i]);
        }
    }
    res = realloc(res, sizeof(char*)*newsentnum);
    if(res == NULL){
        puts("Error: <Memory reallocation failed>");
        exit(1);
    }
    *sentencesnum = newsentnum;
    free(sentences);
    return res;
}

void first_and_last_word_lencounter(const char* sentence, int res[2]){
    int fwcounter = 0;
    int lwcounter = 0;
    int len = strlen(sentence)-1;
    char* fsptr = strchr(sentence, ' ');
    for(int i = 0; i < len; i++){
        if(sentence[i] == ' ' && sentence[i+1] != ' ' && (sentence + i) == fsptr){
            fwcounter = i;
        }
        if(sentence[i] == ' ' && strchr(sentence+i+1, ' ') == NULL){
            lwcounter = len - i -1;
        }
    }
    res[0] = fwcounter;
    res[1] = lwcounter;
}

int comparator(const void* str1, const void* str2){
    const char** f = (const char**)str1;
    const char** s = (const char**)str2;
    int resf[2];
    int ress[2];
    first_and_last_word_lencounter(*f, resf);
    first_and_last_word_lencounter(*s, ress);
    return ress[0] + ress[1] - resf[1] - resf[0];
}

int count_words(char* sentence){
    int wcounter = 0;
    int len = strlen(sentence)-1;
    for(int i = 0; i < len; i++){
        if(sentence[i] == ' ' && sentence[i+1] != ' '){
            wcounter++;
        }
    }
    wcounter++;
    return wcounter;
}

int is_mul_three(char* sentence){
    return !(count_words(sentence) % 3);
}
