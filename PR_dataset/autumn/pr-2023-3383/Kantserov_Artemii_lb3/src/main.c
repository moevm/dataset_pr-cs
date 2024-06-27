#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFER_SIZE 100

int check_word(char* start, char* end){
    
    if (!start || !end || ((end-start)<=2)){
        return 1;
    }
    while ((start <= end) && (isdigit(*start) || isdigit(*end))){
        while (isdigit(*start) && (start <= end)){
            start++;
        }
        while (isdigit(*end) && (start <= end)){
            end--;
        }
    }
    while (start <= end){
        if (isdigit(*start)){
            return 0;
        } else {
            start += (start <= end);
        }
        if (isdigit(*end)){
            return 0;
        } else {
            end -= (start <= end);
        }
    }
    return 1;
}

int main(){
    int n = 0;
    int m = 0;
    int index = 0;
    int size = BUFER_SIZE;
    char* str = (char*) calloc(size, sizeof(char));
    char* start_word = NULL;
    char* end_word = NULL;
    char symbol;
    while ((symbol = getchar()) != '!') {
        if ((symbol != '.') && (symbol != ';') && (symbol != '?')){
            if ((index == 0) && (isblank(symbol))){
                continue;
            }
            if (index+3 >= size) {
                size += BUFER_SIZE;
                char *ptr = realloc(str, size * sizeof(char));
                str = (char*) ptr;
            }
            str[index++] = symbol;
            if (isblank(str[index-1])) {
                if (index >= 2) {
                    if (!isblank(str[index-2])){
                        end_word = str + index - 2;
                        if (!check_word(start_word, end_word)){
                            str[0] = '\0';
                        }
                    }
                }
            } else {
                if (index >= 2){
                    if (isblank(str[index-2])){
                        start_word = str + index-1;
                    }
                } else {
                    start_word = str + index - 1;
                }
            }
        } 
        else {
            str[index++] = symbol;
            if (!isblank(str[index-2])){
                end_word = str + index - 2;
                if (!check_word(start_word, end_word)){
                    str[0] = '\0';
                }
            }
            n++;
            if (str[0] != '\0'){
                m++;
            }
            str[index++] = '\n';
            str[index++] = '\0';
            index = 0;
            start_word = NULL;
            printf("%s", str);
        }
    }
    str[index++] = '!';
    str[index++] = '\n';
    str[index++] = '\0';
    printf("%s", str);
    printf("Количество предложений до %d и количество предложений после %d\n", n, m);
    free(str);
    return 0;
}

