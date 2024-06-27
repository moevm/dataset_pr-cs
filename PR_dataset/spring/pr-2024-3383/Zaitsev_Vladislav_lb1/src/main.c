#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#define STEP 30
#define TEXT_STEP 10
char *read_sent(){
    int sent_len = STEP;
    char *sent = (char *)malloc(sizeof(char) * sent_len);   
    int current_len = 0;
    char temp;
    do{
        if (current_len >= sent_len - 1){
            char *t = (char *)realloc(sent, (sent_len + STEP) * sizeof(char));
            if (!t){
                printf("No memmory!");
                free(sent);
                return NULL;
            }
            sent_len += STEP;
            sent = t;
        }
        temp = getchar();
        sent[current_len] = temp;
        current_len++;
    }while (temp != '\n' && temp != EOF);
    sent[current_len - 1] = '\0';
    return sent;
}
char **read_text(int *ltext){
    int text_len = TEXT_STEP;
    char **text = (char **)malloc(text_len * sizeof(char *));
    int cur_len = 0;
    char *temp;
    do{
        if (cur_len >= text_len - 1){
          char **t = (char **)realloc(text, (text_len + TEXT_STEP) * sizeof(char *));
            if (!t){
                printf("No memmory!");
                free(text);
                return NULL;
            }
            text = t;
            text_len += TEXT_STEP;
        }
        temp = read_sent();
        text[cur_len++] = temp;
    }while(strcmp(text[cur_len - 1], "Fin.") != 0);
    *ltext = cur_len;
    return text;
}
int main()
{
    int len_text;
    char **new_text = read_text(&len_text);
    regex_t re;
    size_t maxGroups = 3;
    regmatch_t groupArray[maxGroups];
    char pattern[100] = "([_A-Za-z0-9]+)@[-_A-Za-z0-9]+: ?~ ?# (.+)"; // #([_-0-9A-Z a-z]+)\n
    if (regcomp(&re, pattern, REG_EXTENDED)){
        printf("Can't compile regular expression\n");
        return 0;
    }
    for(int i = 0; i < len_text; i++){
        if(regexec(&re, new_text[i], maxGroups, groupArray, 0) == 0){
            for(int j = groupArray[1].rm_so; j < groupArray[1].rm_eo;j++){
            
                printf("%c",new_text[i][j]);
            }
            printf(" - ");
            for(int j = groupArray[2].rm_so; j < groupArray[2].rm_eo;j++){
            
                printf("%c",new_text[i][j]);
        }
        printf("\n");
    }
}
    for(int i = 0; i < len_text; i++){
        free(new_text[i]);
    }
    regfree(&re);
    free(new_text);
    return 0;
}
