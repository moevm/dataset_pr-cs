#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* readText(){
    int size = 0;
    int capacity = 1;
    int flag = 0;
    char ch = getchar();
    char* text = (char*) malloc(sizeof(char) + 1);
    while (flag != 1){
        if (size + 1 >= capacity){
            capacity *= 2;
            char* new_buf = (char*) realloc(text,capacity * sizeof(char));
            text = new_buf;
        }
        if (ch == '.' && text[size - 1] == 'n' && text[size - 2] == 'i' && text[size - 3] == 'F'){
            text[size] = ch;
            flag = 1;
        }
        text[size++] = ch;
        ch = getchar();
    }
    text[size] = '\0';
    return text;
}

void findCommandsByRegExp(char* str){
    int maxGroups = 3;
    char* regexString = "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+:\\s?~\\s?#\\s(.+)";
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];
    regcomp(&regexCompiled, regexString, REG_EXTENDED);

    if (regexec(&regexCompiled, str, maxGroups, groupArray,0) == 0){
        for (int i = 1; i < maxGroups; i++){
            if (groupArray[i].rm_so != -1){
                for (int j = groupArray[i].rm_so; j < groupArray[i].rm_eo; j++){
                    if ((j == groupArray[1].rm_eo - 1)){
                        printf("%c - ",str[j]);
                    }
                    if ((j == groupArray[2].rm_eo - 1)){
                        printf("%c\n",str[j]);
                    }
                    if ((j != groupArray[1].rm_eo - 1 ) && ((j != groupArray[2].rm_eo - 1))) {
                        printf("%c",str[j]);
                    }
                }
            }
        }
    }
}

void splitText(char* txt){
    char* sep = "\n";
    char* ptr;
    ptr = strtok(txt,sep);
    while(ptr != NULL){
        findCommandsByRegExp(ptr);
        ptr = strtok(NULL,sep);
    }
}

int main(){
    char* text = readText();
    splitText(text);
    return 0;
}