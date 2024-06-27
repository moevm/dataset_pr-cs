#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#define TEXT_MAX_SIZE 100
#define NUMBER_OF_SENTENCES 10
#define REGULAR_EXPRESSION "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+:[ ]*[~][ ]*[#] (.*)"

void memory_error(){
    fprintf(stderr, "Error with memory allocation!");
    exit(1);
}

char** read_text(char** text){
    int overflow_sent = 0;
    int overflow_symb = 0;
    char* sent = calloc(TEXT_MAX_SIZE, sizeof(char));
    if (sent == NULL){
        memory_error();
    }
    int index = 0;
    int len = 0;
    char symbol;
    while (1){
        symbol = getchar();

        sent[index++] = symbol;

        if ((TEXT_MAX_SIZE + overflow_symb) <= index){
            overflow_symb++;
            sent = realloc(sent, (TEXT_MAX_SIZE + overflow_symb) * sizeof(char));
            text[len] = realloc(sent, (TEXT_MAX_SIZE + overflow_symb) * sizeof(char));
            if (sent == NULL || text[len] == NULL){
                memory_error();
            }
        }

        if (strstr(sent, "Fin.") != NULL){
            text[len++] = strdup(sent);
            free(sent);
            break;
        }

        if (symbol == '\n'){
            sent[index - 1] = '\0';
            text[len++] = strdup(sent);
            overflow_symb = 0;
            index = 0;
            free(sent);
            sent = calloc(TEXT_MAX_SIZE, sizeof(char));
            if (sent == NULL){
                memory_error();
            }
        }

        if ((NUMBER_OF_SENTENCES + overflow_sent) <= len){
            overflow_sent++;
            text = realloc(text, (NUMBER_OF_SENTENCES + overflow_sent) * sizeof(char*));
            text[NUMBER_OF_SENTENCES + overflow_sent - 1] = calloc(TEXT_MAX_SIZE, sizeof(char));
            if (text == NULL || text[NUMBER_OF_SENTENCES + overflow_sent - 1] == NULL){
                memory_error();
            }
        }
    }
    return text;
}

void find_commands(char** text){
    regex_t reegex;
    size_t m = 3;
    regmatch_t matchptr[m];
 
    int value;
    int flag = 0;
    value = regcomp(&reegex, REGULAR_EXPRESSION, REG_EXTENDED);
    for (int i = 0; strstr(text[i], "Fin.") == NULL; i++){
        value = regexec(&reegex, text[i], m, matchptr, 0);
        if (value == 0){
            if (flag == 0){
                flag = 1;
            }
            else{
                printf("\n");
            }
            for (int x = 1; x < m; x++)
            {
                if (matchptr[x].rm_so == -1)
                    break;

                for(int j=matchptr[x].rm_so;j<matchptr[x].rm_eo;j++)
                    printf("%c",text[i][j]);
                if (x == 1){
                    printf(" - ");
                }
            }
        }
    }
    regfree(&reegex);
}

int main() {
    char **text = malloc(NUMBER_OF_SENTENCES * sizeof(char*));
    if (text == NULL) {
        memory_error();
    }
    for(int i = 0; i < NUMBER_OF_SENTENCES; i++){
        text[i] = calloc(TEXT_MAX_SIZE, sizeof(char));
        if (text[i] == NULL) {
            memory_error();
        }
    }
    text = read_text(text);
    find_commands(text);
    int k = 0;
    while (strstr(text[k], "Fin.") == NULL){
        free(text[k++]);
    }
    free(text[k]);
    free(text);
}