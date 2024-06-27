#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "oper.h"
int main(){
    int size=100;
    int operation;
    scanf("%d", &operation);
    int array[size];
    int input_length=input(array, size);
    oper(array, input_length, operation);
    return 0;
}
