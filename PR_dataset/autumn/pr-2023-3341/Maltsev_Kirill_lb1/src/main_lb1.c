#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ARR_SIZE 100
#define BUF_SIZE 2048

void get_input(char[], char*);
void fill_array(char[], int[], int*);
void allocator(char, int[], int);
int index_first_even(int[], int);
int index_last_odd(int[], int );
int sum_between_even_odd(int[], int);
int sum_before_even_and_after_odd(int[], int);

int main() {
    char buf[BUF_SIZE];
    char type;
    int array[ARR_SIZE];
    int size = 0;

    get_input(buf, &type);
    fill_array(buf, array, &size);
    allocator(type, array, size);
    return 0;
}

void get_input(char buf[], char *type) {
    fgets(buf, BUF_SIZE, stdin);
    *type = buf[0];
    if (buf[1] != ' ') *type = '-';
}

void fill_array(char buf[], int array[], int *size) {
    char *substr;
    substr = strtok(buf, " ");
    substr = strtok(NULL, " ");

    while (substr != NULL) {
        array[(*size)++] = atoi(substr);
        substr = strtok(NULL, " ");
    }
}

void allocator(char type, int array[], int size) {
    switch(type) {
    case '0':
        printf("%d\n", index_first_even(array, size));
        break;
    case '1':
        printf("%d\n", index_last_odd(array, size));
        break;
    case '2':
        printf("%d\n", sum_between_even_odd(array, size));
        break;
    case '3':
        printf("%d\n", sum_before_even_and_after_odd(array, size));
        break;
    default:
        printf("Данные некорректны\n");
    }
}

int index_first_even(int array[], int size) {
    for (int i = 0; i < size; i++) {
        if (abs(array[i]) % 2 == 0) return i;
    }
}

int index_last_odd(int array[], int size) {
    for (int i = size-1; i >= 0; i--) {
        if (abs(array[i]) % 2 != 0) return i;
    }
}

int sum_between_even_odd(int array[], int size) {
    int sum = 0;
    for (int i = index_first_even(array, size); i < index_last_odd(array, size); i++) {
        sum += abs(array[i]);
    }
    return sum;
}

int sum_before_even_and_after_odd(int array[], int size) {
    int sum = 0;
    for (int i = 0; i < index_first_even(array, size); i++) {
        sum += abs(array[i]);
    }
    for (int i = index_last_odd(array, size); i < size; i++) {
    	sum += abs(array[i]);
    }
    return sum;
}
