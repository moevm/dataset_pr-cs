#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define END_OF_STR '\0'

char **input(int *quantity_of_str);
void delete_tabs(char **array, int quantity_of_str);
void output(char **array, int quantity_of_str);

int main() {
    int len_of_arr = 0;

    char **text = input(&len_of_arr);

    delete_tabs(text, len_of_arr);

    output(text, len_of_arr);

    for (int i = 0; i < len_of_arr; i++) {
        free(text[i]);
    }
    free(text);
    return 0;
}

char **input(int *quantity_of_str){
    size_t capacity_of_str = 1;

    char **text = malloc(sizeof(char*)*capacity_of_str);

    while(1){
        size_t quantity_of_char = 0;
        size_t capacity_of_char = 1;
        int is_end = 0;

        char symbol = getchar();
        text[*quantity_of_str] = malloc(sizeof(char) * capacity_of_char);


        while(1){
            if(symbol == '.' || symbol == ';' || symbol == '?' || symbol == '!'){
                if(symbol == '!'){
                    is_end = 1;
                }
                text[*quantity_of_str][quantity_of_char] = symbol;
                break;
            }

            text[*quantity_of_str][quantity_of_char] = symbol;

            quantity_of_char++;

            if(quantity_of_char >= capacity_of_char){
                capacity_of_char += 2;
                text[*quantity_of_str] = realloc(text[*quantity_of_str], sizeof(char)*capacity_of_char);
            }

            symbol = getchar();
        }

        text[*quantity_of_str][quantity_of_char + 1] = END_OF_STR;

        (*quantity_of_str)++;
        if(*quantity_of_str >= capacity_of_str){
            capacity_of_str += 2;
            text = realloc(text, sizeof(char*)*capacity_of_str);
        }


        if(is_end){
            break;
        }
    }

    return text;
}
void delete_tabs(char** array, int quantity_of_str) {
    for (int i = 0; i < quantity_of_str; i++) {
        int length = strlen(array[i]);
        int j = 0;

        while (array[i][j] == ' ' || array[i][j] == '\t') {
            j++;
        }
        memmove(array[i], array[i] + j, length - j + 1);
    }
}
void output(char **array, int quantity_of_str){
    int quantity_of_delete = 0;

    for (int i = 0; i < quantity_of_str; i++) {
        int count = 0;
        for (int j = 0; array[i][j]; j++) {
            if(isupper(array[i][j])){
                count++;
            }
        }
        if(count > 1){
            quantity_of_delete++;
        }else{
            printf("%s\n", array[i]);
        }
    }
    printf("Количество предложений до %d и количество предложений после %d", quantity_of_str - 1, quantity_of_str - quantity_of_delete - 1);
}