#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 10000

int read_str(char *str);

int main(){

    int count_sentence_before = 0;
    int count_sentence_after = 0;
    char * new_str = malloc(STR_SIZE * sizeof(char));
    
    do{
        int flag = read_str(new_str);

        getchar();

        if(flag){
            printf("%s\n", new_str);
            count_sentence_before++;
            count_sentence_after++;
        }
        else{
            count_sentence_before++;
        }
    } while(strcmp(new_str, "Dragon flew away!") != 0);

    free(new_str);

    printf("Количество предложений до %d и количество предложений после %d\n", count_sentence_before-1, count_sentence_after-1);

    return 0;
}

int read_str(char *str){

    int i = 0;
    int flag = 1;

    do{
        char symbol = getchar();
        if(symbol != '\n' && symbol != '\t'){
            str[i] = symbol;
            i++;
            if(symbol == '7'){
                flag = 0;
            }
        }
    } while(str[i - 1] != '.' && str[i - 1] != ';' && str[i - 1] != '?' && str[i - 1] != '!');

    str[i] = '\0';

    return flag;
}