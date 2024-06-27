#include <stdio.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"

#define D "%d\n"
#define N 100

void input_key(int* key_ptr){
    scanf("%d", key_ptr);
}

void input_array(int array[], int* array_size_ptr){
    char space = ' ';
    while(*array_size_ptr < N && space == ' '){
        scanf("%d%c", &array[*array_size_ptr], &space);
        (*array_size_ptr)++;
    }
}

void key_action(int array[], int array_size, int key){
    switch(key){
        case 0:
            printf(D, index_first_zero(array, array_size));
            break;
        case 1:
            printf(D, index_last_zero(array, array_size));
            break;
        case 2:
            printf(D, sum_between(array, array_size));
            break;
        case 3:
            printf(D, sum_before_and_after(array, array_size));
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }
}
int main(){
    int key;
    input_key(&key);

    int array[N];
    int array_size = 0;
    input_array(array, &array_size);

    key_action(array, array_size, key);
}
