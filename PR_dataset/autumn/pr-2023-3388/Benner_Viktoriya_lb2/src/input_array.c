#include <stdio.h>
#include "input_array.h"

void input_array(char symbol, int size, int arr[]){
    while(symbol!='\n')
    {
        scanf("%d%c", &arr[size], &symbol);
        size++;
    }
}