#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int main() {

    char* text = (char*)malloc(sizeof(char)*10000);
    int text_size = 0;
    int text_capacity = 10000;

    while(1){
        char string[10000];
        fgets(string, 10000, stdin);
        strcat(text, string);
        text_size+=strlen(string)*sizeof(char);
        if(text_size >= text_capacity-1000){
            text_capacity += 10000;
            text = (char*)realloc(text, sizeof(char)*text_capacity);
        }
        if(strcmp(string, "Fin.") == 0){
            break;
        }
    }
    regex_t regex;
    const char* type = "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+:[ ]*~[ ]*# (.+)";

    if(regcomp(&regex, type , REG_EXTENDED)){
        fprintf(stderr, "Error: Regular expression compilation failed.");
    }

    int max_groups = 3;
    char* token = (char*)strtok(text, "\n");
    while(token){
        regmatch_t groupArray[max_groups];
        if(regexec(&regex, token, max_groups, groupArray, 0) == 0){
            printf("%.*s - %.*s\n", (int)(groupArray[1].rm_eo - groupArray[1].rm_so), &token[groupArray[1].rm_so], (int)(groupArray[2].rm_eo - groupArray[2].rm_so), &token[groupArray[2].rm_so]);
        }
        token = (char*)strtok(NULL, "\n");
    }

    free(text);
    regfree(&regex);
    return 0;
}