#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEXT_SIZE 100
#define TERM "Dragon flew away!"

int checking_the_last_symbol(char *text){
    int len_text = strlen(text);
    int correct = 0;
    if(text[len_text-1] == '?'){
               correct = 1;
    }
    return correct;
}

int main(){
    int size_text = TEXT_SIZE;
    char* text = (char*)malloc(TEXT_SIZE*sizeof(char));
    int index = 0;
    int initial_count = 0, end_count = 0;
    char symbol;
    while(strcmp(text,TERM)){
        symbol = getchar();
        if((index==0) && ((symbol=='\t') || (symbol==' ')))
	        continue;
        if (index == size_text-2){
            size_text += TEXT_SIZE;
            text = (char*)realloc(text, size_text*sizeof(char));
        }
        text[index] = symbol;
        index++;
        if ((symbol== '.') || (symbol == ';')){
            text[index]='\0';
            printf("%s\n", text);
            free(text);
            text = (char*)calloc(size_text, sizeof(char));
            initial_count++;
            end_count++;
            index = 0;
        }
        int correct_text = checking_the_last_symbol(text);
        if (correct_text == 1){
            initial_count++;
            index = 0;
            free(text);
            text = (char*)calloc(size_text,sizeof(char));
        }   
  }
    printf("%s\n", text);
    printf("Количество предложений до %d и количество предложений после %d", initial_count, end_count);
    free(text);

    return 0;
}
