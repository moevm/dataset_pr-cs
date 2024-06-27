#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#define BLOCK_SIZE 10
#define END_OF_TEXT "Fin."

int main(){
    char* regex_string = "([A-Za-z0-9_]+)@([A-Za-z0-9_-]+):\\s*~\\s*#\\s(.+)";
    size_t max_groups = 4;

    regex_t regex_compiled;
    regmatch_t group_array[max_groups];

    regcomp(&regex_compiled, regex_string, REG_EXTENDED);

    int capacity = BLOCK_SIZE;
    char symbol = getchar();
    char* input_text = (char*)malloc(capacity);
    if(input_text == NULL){
        printf("Memory error");
        exit(0);
    }
    int idx = 0;
    while(1){
        input_text[(idx)++] = symbol;
        if(idx == capacity - 1){
            capacity += BLOCK_SIZE;
            input_text = (char*)realloc(input_text,capacity);
            if(input_text == NULL){
                printf("Memory error");
        	exit(0);
            }
        }
        symbol = getchar();
        if(strstr(input_text, END_OF_TEXT)){
            break;
        }
    }

    int sentences = 0;
    int amount_of_char = 0;
    int max_amount_of_char = 0;
    int amount_of_str = 0;
    for(int i = 0; i<idx; i++){
        if(input_text[i] == '\n'){
            sentences++;
            amount_of_char++;
            if(amount_of_char>max_amount_of_char){
                max_amount_of_char = amount_of_char;
            }
            amount_of_char = 0;
        }
        else{
            amount_of_char++;
        }
    }

    char** text = (char**)malloc(sizeof(char*) * (sentences+1));
    if(text == NULL){
        printf("Memory error");
        exit(0);
    }
    for(int i = 0; i<sentences; i++){
        text[i] = (char*)malloc(sizeof(char) * (max_amount_of_char+2));
        if(text[i] == NULL){
            printf("Memory error");
            exit(0);
        }
    }

    int chars = 0;
    for(int i = 0; i<idx; i++){
        if(input_text[i] == '\n'){
            text[amount_of_str][chars] = '\n';
            text[amount_of_str][chars+1] = '\0';
            if (regexec(&regex_compiled, text[amount_of_str], max_groups, group_array, 0) == 0){
                for (int i = group_array[1].rm_so; i < group_array[1].rm_eo; ++i){
                    printf("%c",text[amount_of_str][i]);
                }
                printf(" - ");
                for (int i = group_array[3].rm_so; i < group_array[3].rm_eo; ++i){
                    printf("%c",text[amount_of_str][i]);
                }
            }
            chars = 0;
        }
        else{
            text[amount_of_str][chars] = input_text[i];
            chars++;
        }
    }
    free(input_text);
    for(int i = 0; i<amount_of_str; i++){
        free(text[i]);
    }
    free(text);
    regfree(&regex_compiled);
    return 0 ;
}
