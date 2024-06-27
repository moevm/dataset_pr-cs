#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../header/input.h"


void getFuncID(char* func_id){
    *func_id=getchar();
}

char* getKeyWord(){
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

char* getText(int* sentence_num){
    char* text= malloc(sizeof(char));
    int line_break_counter=0;
    int capacity=1;
    char input_ch=getchar();
    int text_len=0;

    while (line_break_counter<2){
        if (input_ch=='.'){
            (*sentence_num)++;
        }

        text[text_len]=input_ch;
        (text_len)++;

        if (text_len+1 >= capacity){
            capacity *=2;
            text= realloc(text,sizeof(char )*capacity );
        }

        if ((input_ch=getchar())=='\n'){
            line_break_counter++;
        }else{
            line_break_counter=0;
        }
    }
    text[(text_len)-1]='\0';
    return text;
}

char** split(char* text, int* sentence_num){
    char** split_text= (char**)calloc(*sentence_num, sizeof(char*));
    char* isent=strtok(text, ".");
    int i=0;
    while (isent!=NULL){
        while (isspace(*isent))
            isent++;
        split_text[i]= calloc(strlen(isent)+1, sizeof(char));
        split_text[i]=isent;
        isent= strtok(NULL, ".");
        i++;
    }
    return split_text;
}