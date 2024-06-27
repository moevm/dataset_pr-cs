#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BASIC_TEXT_SIZE 100
#define PHRASE "Dragon flew away!"

int checking_last_sign(char* text){
    if(text[strlen(text)-1] == '?'){
        return 1;
    }
    return 0;
}

void print_result(char* text, int initial_cnt, int end_cnt){
    printf("%s\n", PHRASE);
    printf("Количество предложений до %d и количество предложений после %d\n", initial_cnt, end_cnt);
}

void editing_of_text(char* text, int* size_of_text, int* initial_cnt, int* end_cnt){
    char symbol;
    int index = 0;
    while((symbol = getchar())!='!'){
        if((index == 0) && ((symbol == '\t') || (symbol == ' '))){
            continue;
        }
        if (index == (*size_of_text) - 2){
            (*size_of_text) += BASIC_TEXT_SIZE;
            text = realloc(text, (*size_of_text)*sizeof(char));
        }
        text[index] = symbol;
        index++;
        if((symbol == '.') || (symbol == ';')){
            text[index] = '\0';
            printf("%s\n", text);
            free(text);
            text = (char*)calloc((*size_of_text), sizeof(char));
            (*initial_cnt)++;
            (*end_cnt)++;
            index = 0;
        }
        if (checking_last_sign(text) == 1)
        {
            (*initial_cnt)++;
            index = 0;
            free(text);
            text = (char*)calloc((*size_of_text), sizeof(char));
        }
    }
}

int main(){
    int size_of_text = BASIC_TEXT_SIZE;
    char* text = malloc(BASIC_TEXT_SIZE*sizeof(char));
    int initial_cnt = 0;
    int end_cnt = 0;
    editing_of_text(text, &size_of_text, &initial_cnt, &end_cnt);
    print_result(text, initial_cnt, end_cnt);
    return 0;
}
