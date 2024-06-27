#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define BLOCK_SIZE 10


int main(){
    char* str = (char*)malloc(BLOCK_SIZE);
    size_t capacity = BLOCK_SIZE;
    size_t idx = 0;
    str[idx] = getchar();
    size_t counter_before = 0;
    size_t counter_after = 0;
    while(1){
        if(idx == 0 && isspace(str[idx])){
            str[idx] = getchar();
            continue;
        }

        if(str[idx] == '.' || str[idx] == ';' || str[idx] == '?'){
            str[idx+1] = '\0';
            if(strchr(str, '7') == NULL){
                puts(str);
                counter_after++;
            }
            counter_before++;
            free(str);
            str = (char*)malloc(BLOCK_SIZE);
            idx = 0;
            capacity = BLOCK_SIZE;
            str[idx] = getchar();
            continue;
        }

        if(str[idx] == '!'){
            str[idx+1] = '\0';
            puts(str);
            break;
        }
        idx++;
        if(idx == capacity){
            str = (char*)realloc(str, capacity+BLOCK_SIZE);
            capacity += BLOCK_SIZE;
        }
        str[idx] = getchar();

    }

    printf("Количество предложений до %lu и количество предложений после %lu", counter_before, counter_after);
    return 0;
}
