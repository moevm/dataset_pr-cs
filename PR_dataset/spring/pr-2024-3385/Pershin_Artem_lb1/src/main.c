#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define BLOCK 42
#define REGEX "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+: ?~ ?# (.*)"
#define STOP_W "Fin."
#define MERROR Memory allocation error


char* read_string(){
    int len = BLOCK;
    char* str = (char*)malloc(sizeof(char) * len);
    if(str == NULL){
        printf("MERROR\n");
        exit(1);
    }
    char* new_str;
    char* stop_w = STOP_W;
    int i = 0;
    char c;
    scanf("%c", &c);
    for(; c != '\n'; i++){
        str[i] = c;
        scanf("%c", &c);
        if(i + 1 >= len){
            len += BLOCK;
            new_str = realloc(str, sizeof(char) * len);
            if(new_str == NULL){
                printf("MERRORn");
                free(str);
                exit(1);
            }
            str = new_str;
        }
        str[i+1] = '\0';
        if(!strcmp(str, stop_w)){
            return str;
        }
    }
    return str;
}


int main(){
    regex_t reg;
    regmatch_t matches[3];
    char* reg_string = REGEX;
    char* stop_w = STOP_W;
    char* str;
    int i;
    if (regcomp(&reg, reg_string, REG_EXTENDED)){
        printf("Failed to compile regex pattern\n");
        exit(1);
    }
    while(1){
        str = read_string();
        if(!strcmp(str, stop_w)){
            free(str);
            break;
        }
        if(!regexec(&reg, str, 3, matches, 0)){
            for(i = matches[1].rm_so; i < matches[1].rm_eo; i++){
                printf("%c", str[i]);
            }
            printf(" - ");
            for(i = matches[2].rm_so; i < matches[2].rm_eo; i++){
                printf("%c", str[i]);
            }
            printf("\n");
        }
        free(str);
    }
    regfree(&reg);
    return 0;
}