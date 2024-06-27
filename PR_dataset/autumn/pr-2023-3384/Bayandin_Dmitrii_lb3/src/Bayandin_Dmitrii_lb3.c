#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define STEP 20
#define MEMORY 200


int format(char* str, int* count_old, int* count_end){
    if(strcmp(str, "Dragon flew away!") == 0){
        printf("%s\n", str);
        printf("Количество предложений до %d и количество предложений после %d", *count_old, *count_old - *count_end);
        return 0;
    }
    *count_old += 1;
    int i = strlen(str);
    int j;
    for(j = 1; j < i - 1; j++){
        if(isdigit(str[j]) && (isalpha(str[j-1]) || isalpha(str[j-1]))){
            if(str[j-1] == ' '){
                continue;
            }
            if(str[j+1] == ' ' || str[j+1] == '.' || str[j+1] == ';' || str[j+1] == '?'){
                continue;
            }
            if(isdigit(str[j-1]) && isdigit(str[j+1])){
                continue;
            }
            *count_end += 1;
            return 1;
        }
    }
    printf("%s\n", str);
    return 1;
}



int main() {
    char* text = malloc(MEMORY*sizeof(char));
    int summ_char = 0;
    int summ_memory = 0;
    int flag = 0;
    int count_end = 0;
    int count_old = 0;
    while(1){
        char c = getchar();
        summ_char += 1;
        if(summ_char == MEMORY + summ_memory){
            text = realloc(text, STEP*sizeof(char));
            summ_memory += STEP;
        }
        if((!flag && (c == ' '))){
            summ_char -= 1;
            continue;
        }
        else{
            flag = 1;
        }
        if(c == '\n' || c == '\t'){
            summ_char -= 1;
            continue;
        }
        if(c == '.' || c == '?' || c == ';' || c == '!'){
            text[summ_char-1] = c;
            text[summ_char] = '\0';
            if(!format(text, &count_old, &count_end)){
                free(text);
                return 0;
                }
            else{
            summ_char = 0;
            summ_memory = 0;
            flag = 0;
            free(text);
            char* text = malloc(MEMORY*sizeof(char));
            continue;
            }
        }
        text[summ_char-1] = c;
    }
}
