#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BLOCK_SIZE 10

char** get_text(int* amount_of_str);
void answer(char** text, int amount_of_str);
void clean_memory(char** text, int amount_of_str);

int main(){
    int amount_of_str = 0;
    char** text = get_text(&amount_of_str);
    answer(text,amount_of_str);
    clean_memory(text,amount_of_str);
    return 0;
}

char** get_text(int* amount_of_str){
    int capacity = BLOCK_SIZE;
    int capacity_of_str = capacity;

    char** text = (char**)malloc(sizeof(char*)*capacity_of_str);

    while(1){
        
        int amount_of_char = 0;
        int capacity_of_char = capacity;

        char symbol = getchar();

        if (symbol==' ' || symbol=='\t' || symbol == '\n'){
            continue;
        }
        text[*amount_of_str] = (char*)malloc(sizeof(char) * capacity_of_char);
        int end_of_text = 0;

        while(1){
            if(symbol == '!'){
                text[*amount_of_str][amount_of_char] = symbol;
                end_of_text = 1;
                break;
            }
            
            if(symbol == '.' || symbol == ';' || symbol == '?'){
                text[*amount_of_str][amount_of_char] = symbol;
                break;
            }

            text[*amount_of_str][amount_of_char] = symbol;

            amount_of_char++;



            if(amount_of_char >= capacity_of_char){
                capacity_of_char *=2;
                text[*amount_of_str] = realloc(text[*amount_of_str], sizeof(char)*(capacity_of_char+1));
            }

            symbol = getchar();
        }

        text[*amount_of_str][amount_of_char + 1] = '\0';

        (*amount_of_str)++;
        if(*amount_of_str >= capacity_of_str){
            capacity_of_str += capacity;
            text = realloc(text, sizeof(char*)*capacity_of_str);
        }


        if(end_of_text){
            break;
        }
    }

    return text;
}
void answer(char** text, int amount_of_str){
    int amount_of_str_after = 0;
    for(int i = 0; i<amount_of_str; i++){
        int count_upper = 0;
        for(int j = 0; text[i][j]; j++){
            if(isupper(text[i][j])){
                count_upper++;
            }
        }
        if(count_upper<=1){
           amount_of_str_after++;
           printf("%s\n", text[i]);
        }
    }
    printf("Количество предложений до %d и количество предложений после %d", amount_of_str - 1,amount_of_str_after - 1);
}

void clean_memory(char** text, int amount_of_str){
    for(int i = 0; i < amount_of_str; i++){
        free(text[i]);
    }
    free(text);
}