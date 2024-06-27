#include <stdio.h>
#include <stdlib.h>
#define MEMORY_STEP 16

int isEndOfWord(char c){
   return c == ' ' || c == '?' || c==',' || c =='.';
}

int check(char *text, int len){
    int flag = 0;
    for(int i = 0;i < len - 2; i++){
        if((i == 0 || text[i-1] == ' ') && text[i] == '5')
            if(text[i+1] == '5' && text[i+2] == '5' && isEndOfWord(text[i+3]))
                flag = 1;
    }
    return flag;
}
int main(){
    int count_before = -1;
    int count_after = -1;
    int str_len = 0;
    char* text = (char*)malloc(MEMORY_STEP*sizeof(char));
    char symbol;
    int number_of_step = 1;
    while(symbol != '!'){
        symbol = getchar();
        if ((str_len == 0 && symbol ==' ') || symbol == '\n' || symbol == '\t')
            continue;
        text[str_len++] = symbol;
        if(str_len == number_of_step*MEMORY_STEP){
            number_of_step++;
            text = (char *)realloc(text, (number_of_step*MEMORY_STEP)*sizeof(char));
        }
        if (symbol == '.' || symbol == ';' || symbol == '?' || symbol == '!'){
            text[str_len] = '\0';
            count_before++;
            if (check(text, str_len) == 0){
                count_after++;
                printf("%s\n", text);
            }
            free(text);
            text = (char*)malloc(MEMORY_STEP*sizeof(char));
            str_len = 0;
            number_of_step = 1;
        }
    }
    printf("Количество предложений до %d и количество предложений после %d", count_before, count_after);
    return 0;
}


