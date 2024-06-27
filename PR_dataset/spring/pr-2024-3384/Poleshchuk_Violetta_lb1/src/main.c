#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

char** make_text(int* text_len){
    char** text = malloc(1000*sizeof(char*));
    do{
        text[(*text_len)]= calloc(1000,sizeof(char));
        fgets(text[(*text_len)], 1000, stdin);
        char *ptr = strchr(text[(*text_len)], '\0');
        text[(*text_len)]= realloc(text[(*text_len)], sizeof(char)* (ptr-text[(*text_len)]));
    } while (!strstr(text[(*text_len)++], "Fin."));
    text = realloc(text, sizeof(char*)*(*text_len));
    return text;
}

int main() {
    size_t maxGroups = 3;
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];
    int text_len = 0;
    char** text = make_text(&text_len);
    char * regexString = "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+: ?~ ?# (.*)\n";
    if (regcomp(&regexCompiled, regexString, REG_EXTENDED)){
        puts("Can't compile regular expression\n");
    }
    int count = 0;
    for (int i = 0; i < text_len; i++){
        if (regexec(&regexCompiled, text[i], maxGroups, groupArray, 0) == 0){
            if (count > 0){
                printf("\n");
            }
            count++;
            for(int index = groupArray[1].rm_so; index < groupArray[1].rm_eo; index++){
                printf("%c", text[i][index]);
            }
            printf(" - ");
            for(int index = groupArray[2].rm_so; index < groupArray[2].rm_eo; index++){
                printf("%c", text[i][index]);
            }
        }
    }
}