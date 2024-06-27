#include "input.h"
#include <stdio.h>

int input(int arr[]){
    char end = getchar();
    int len = 0;

    while (end != '\n')
    {
        scanf("%d", &arr[len++]);
        end = getchar();
    }

    return len;
}