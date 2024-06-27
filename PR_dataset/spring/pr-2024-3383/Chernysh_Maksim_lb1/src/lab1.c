#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define TEXT_STEP 20
#define STR_STEP 20

char* input_str() {
    char ch;
    size_t len = 0;
    size_t size = TEXT_STEP;
    char* str = (char*)malloc(size * sizeof(char));
    if(!str){
        return NULL;
    }
    while(1){
        ch = getchar();
        if(ch == '\n' || ch == EOF){
            str[len] = '\0';
            break;
        }
        if(len + 1 >= size){
            size += TEXT_STEP;
            char* temp = (char*)realloc(str, size * sizeof(char));
            if(!temp){
                free(str);
                return NULL;
            }
            str = temp;
        }
        str[len++] = ch;
    }
    return str;
}

void free_text(char **text, size_t len) {
    for(size_t i = 0; i < len; i++){
        free(text[i]);
    }
    free(text);
}

char** input_text(size_t *text_len){
    size_t len = 0;
    size_t size = TEXT_STEP;
    char** text = (char**)malloc(size * sizeof(char *));
    if(!text) {
        return NULL;
    }
    do{
        if(len + 1 > size){
            size_t new_size = size + TEXT_STEP;
            char **temp = (char**)realloc(text, new_size * sizeof(char *));
            if(!temp){
                free_text(text, len);
                return NULL;
            }
            text = temp;
            size = new_size;
        }
        char *new_str = input_str();
        if(!new_str){
            free_text(text, len);
            return NULL;
        }
        text[len++] = new_str;
    } while(strcmp(text[len - 1], "Fin.") != 0);
    *text_len = len;
    return text;
}

int main(){
    size_t text_len = 0;
    char** text = input_text(&text_len);
    if(!text){
	    printf("Memory allocation error\n");
	    return 0;
    }
    char* regexString = "(\\w+)@[a-zA-Z0-9_-]+: ?~ ?# (.+)";
    regex_t regexCompiled;
    if(regcomp(&regexCompiled, regexString, REG_EXTENDED)){
        free_text(text, text_len);
        printf("Can't compile regular expression\n");
        return 0;
    }
    size_t maxGroups = 3;
    regmatch_t groupArray[maxGroups];
    for(size_t i = 0; i < text_len; i++){
        if(regexec(&regexCompiled, text[i], maxGroups, groupArray, 0) == 0){
            char* group1_start = text[i] + groupArray[1].rm_so;
            size_t group1_len = groupArray[1].rm_eo - groupArray[1].rm_so;
            
            char* group2_start = text[i] + groupArray[2].rm_so;
            size_t group2_len = groupArray[2].rm_eo - groupArray[2].rm_so;
            
            printf("%.*s - %.*s\n", (int)group1_len, group1_start, (int)group2_len, group2_start);
        }
    }
    regfree(&regexCompiled);
    free_text(text, text_len);
    return 0;
}
