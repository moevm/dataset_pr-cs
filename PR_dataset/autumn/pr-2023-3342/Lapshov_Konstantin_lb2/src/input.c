#include "input.h"

int input(int array[]){
    int iterator = 0;
    char symbol;

    do{
        scanf("%d%c", &array[iterator], &symbol);
        iterator++;
    } while(symbol != '\n' && iterator < 100);

    return iterator;
}