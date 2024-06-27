#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"

#define FORMAT_STRING "%d\n"
#define arr_size 20
#define buf_size 2048
void array_up(char buf[], int array[], int *size) {
    char *token_str;
    token_str = strtok(buf, " ");
    token_str = strtok(NULL, " ");

    while (token_str != NULL) {
        array[(*size)++] = atoi(token_str);
        token_str = strtok(NULL, " ");
    }
}
void choiser(char choise, int array[], int size) {
    switch(choise) {
        case '0':
            printf(FORMAT_STRING,index_first_negative(array, size));
            break;
        case '1':
            printf(FORMAT_STRING,index_last_negative(array, size));
            break;
        case '2':
            printf(FORMAT_STRING,multi_between_negative(array, size));
            break;
        case '3':
            printf(FORMAT_STRING,multi_before_and_after_negative(array, size));
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }
}
void get_input_and_process() {
    char buf[buf_size];
    fgets(buf, buf_size, stdin);

    char choise;
    choise = buf[0];

    int array[arr_size];
    int size = 0;

    array_up(buf, array, &size);
    choiser(choise, array, size);
}

int main() {
    get_input_and_process();
    return 0;
}
