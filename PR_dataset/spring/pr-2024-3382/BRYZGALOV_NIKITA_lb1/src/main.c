#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>


char ** text_input(int * num_sentss);
void free_text(char ** text, int num_sentss);


int main() {
    int num_sents = 0;
    int len_name, len_command;
    
    char ** text = text_input(&num_sents);
    char * regexString = "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+: *~ *# (.+)";
    
    regex_t regexCompiled;
    regcomp(&regexCompiled, regexString, REG_EXTENDED);
    
    size_t maxGroups = 3;
    regmatch_t groupArray[maxGroups];
    
    for (int i = 0; i < num_sents; i ++) {
        if (regexec(&regexCompiled, text[i], maxGroups, groupArray, 0) == 0) {
            
            len_name = groupArray[1].rm_eo - groupArray[1].rm_so;
            len_command = groupArray[2].rm_eo - groupArray[2].rm_so;
            
            printf("%.*s - ", len_name, text[i] + groupArray[1].rm_so);
            printf("%.*s\n", len_command, text[i] + groupArray[2].rm_so);
        }
    }
    
    free_text(text, num_sents);
    regfree(&regexCompiled);
    return 0;
}


char ** text_input(int * num_sentss) {
    int i = 0, j = 0, flag = 1;
    char symbol;
    int sent_size, step = 50;
    char ** text = malloc(sizeof(char*));

    while (flag) {
        j = 0;
        sent_size = step;
        text = realloc(text, sizeof(char*) * (i + 1));
        text[i] = malloc(sizeof(char) * step);
        
        while (1) {
            if (j + 5 > sent_size) {
                sent_size += step;
                text[i] = realloc(text[i], sizeof(char) * sent_size);
            }

            symbol = getchar();
            text[i][j] = symbol;
            text[i][j + 1] = '\0';
            
            if (symbol == '\n') {
                text[i][j] = '\0';
                break;
            }
            if (strcmp(text[i], "Fin.\0") == 0) {
                flag = 0;
                break;
            }
            
            j ++;
        }
        
        if (flag == 0) 
            break;
            
        i ++;
    }
    
    *num_sentss = i + 1;
    return text;
}


void free_text(char ** text, int num_sentss) {
    for (int i = 0; i < num_sentss; i ++)
        free(text[i]);
    free(text);
}
