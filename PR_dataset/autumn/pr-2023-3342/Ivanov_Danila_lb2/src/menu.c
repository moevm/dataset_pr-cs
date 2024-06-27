#include <stdio.h>
#include "input.h"
#include "output.h"
#define ARR_SIZE 100

int main(){
    int number_of_func;
    int arr[ARR_SIZE];
    char end;
    int len = 0;
    scanf("%d", &number_of_func);
    
    len = input(arr);

    output(number_of_func, arr, len);
    return 0;
}