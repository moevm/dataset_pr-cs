#include <stdio.h>

#define ARR_MAX_SIZE 20

int console_input_arr(int arr[]){
    int length = 0;
    char space = ' ';
    while(length < ARR_MAX_SIZE && space == ' '){
    	scanf("%d%c", &arr[length], &space);
    	length++;
    }
    return length;
}