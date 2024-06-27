#include "input.h"
#include <stdio.h>

int input(int arr[]){
    
    char symbol = getchar();
    int len = 0;

    while (symbol != '\n')
    {
        scanf("%d", &arr[len++]);
        symbol = getchar();
    }
    
    return len;
}