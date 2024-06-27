#include <stdio.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"

#define ARRAY_SIZE 100
#define OUT "%d\n"

void input(int* flag, int* actual_size_of_array, int array[]){
    *actual_size_of_array = 0;
    char separator;

    scanf("%d", flag);
    scanf("%c", &separator);
    while (separator != '\n' && *actual_size_of_array < ARRAY_SIZE) {
        scanf("%d", &array[*actual_size_of_array]);
        scanf("%c", &separator);
        *actual_size_of_array += 1;
    }
}

void output(int flag, int actual_size_of_array, int array[]) {
    switch (flag)
    {
    case 0:
        printf(OUT, index_first_zero(array, actual_size_of_array));
        break;
    case 1:
        printf(OUT, index_last_zero(array, actual_size_of_array));
        break;
    case 2:
        printf(OUT, sum_between(array, actual_size_of_array));
        break;
    case 3:
        printf(OUT, sum_before_and_after(array, actual_size_of_array));
        break;
    default:
        printf("Данные некорректны\n");
        break;
    }
}

int main(){
    int flag, actual_size_of_array;
    int array[ARRAY_SIZE];

    input(&flag, &actual_size_of_array, array);
    output(flag, actual_size_of_array, array);

    return 0;
}
