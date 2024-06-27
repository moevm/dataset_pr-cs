#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define arr_size 20
#define buf_size 2048

int index_first_negative(int array[], int size) {
    int product = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] < 0) {
            product = i;
            break;
        }
    }
    return product;
}

int index_last_negative(int array[], int size) {
    int product = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] < 0) {
            product = i;
        }
    }
    return product;
}

int multi_between_negative(int array[], int size) {
    int x = index_first_negative(array, size);
    int y = index_last_negative(array, size);
    int product = 1;
    for (int i = x; i < y; i++) {
        product *= array[i];
    }
    return product;
}

int multi_before_and_after_negative(int array[], int size) {
    int product = 1;
    int x = index_first_negative(array, size);
    int y = index_last_negative(array, size);
    for (int i = 0; i < x; i++) {
        product *= array[i];
    }
    for (int j = y; j < size; j++) {
        product *= array[j];
    }
    return product;
}

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
            printf("%d\n",index_first_negative(array, size));
            break;
        case '1':
            printf("%d\n",index_last_negative(array, size));
            break;
        case '2':
            printf("%d\n",multi_between_negative(array, size));
            break;
        case '3':
            printf("%d\n",multi_before_and_after_negative(array, size));
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
