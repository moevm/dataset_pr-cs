#include <stdio.h>
#include <stdlib.h>
#define MAX_ARRAY_SIZE 100
#define INPUT_ERROR_SIGN -9999
#define OUTPUT_ERROR_STRING "Данные некорректны"

int index_first_negative(int arr[], int arr_size){
    int result = INPUT_ERROR_SIGN;
    for (int j = 0; j < arr_size; j++){
       if (arr[j] < 0){
           result = j;
           break;
       }
    }
    if (result == INPUT_ERROR_SIGN){
        printf("%s\n", OUTPUT_ERROR_STRING);
    }
    else{
        printf("%d\n", result);
        return result;
    }
    
}
   
int index_last_negative(int arr[], int arr_size){
    int result = INPUT_ERROR_SIGN;
    for (int j = 0; j < arr_size; j++){
        if (arr[j] < 0){
            result = j;
        }
    }
    if (result == INPUT_ERROR_SIGN){
        printf("%s\n", OUTPUT_ERROR_STRING);
    }
    else{
        printf("%d\n", result);
        return result;
    }
}
   
int sum_between_negative(int arr[], int arr_size){
    int sum = 0;
    int start = INPUT_ERROR_SIGN;
    for (int j = 0; j < arr_size; j++){
       if (arr[j] < 0){
           start = j;
           break;
       }
    }
    int end = INPUT_ERROR_SIGN;
    for (int j = 0; j < arr_size; j++){
        if (arr[j] < 0){
            end = j;
        }
    }
    if (start == INPUT_ERROR_SIGN || end == INPUT_ERROR_SIGN){
        sum = INPUT_ERROR_SIGN;
    }
    else{
        for (int j = start; j < end; j++){
        sum = sum + abs(arr[j]);
        }
    }
    if (sum == INPUT_ERROR_SIGN){
        printf("%s\n", OUTPUT_ERROR_STRING);
    }
    else{
        printf("%d\n", sum);
    }
}
   
int sum_before_and_after_negative(int arr[], int arr_size){
    int sum = 0;
    int start = INPUT_ERROR_SIGN;
    for (int j = 0; j < arr_size; j++){
       if (arr[j] < 0){
           start = j;
           break;
       }
    }
    int end = INPUT_ERROR_SIGN;
    for (int j = 0; j < arr_size; j++){
        if (arr[j] < 0){
            end = j;
        }
    }
    if (start == INPUT_ERROR_SIGN || end == INPUT_ERROR_SIGN){
        sum = INPUT_ERROR_SIGN;
    }
    else{
        for (int j = 0; j < start; j++){
            sum = sum + abs(arr[j]);
        }
        for (int k = end; k < arr_size; k++){
            sum = sum + abs(arr[k]);
        }
    }
    if (sum == INPUT_ERROR_SIGN){
        printf("%s\n", OUTPUT_ERROR_STRING);
    }
    else{
        printf("%d\n", sum);
    }
    
}

int main(){
   int command;
   int i = 0;
   int nums[MAX_ARRAY_SIZE];
   char space = ' ';
   
   scanf("%d", &command);
   while (i < MAX_ARRAY_SIZE && space == ' '){
       scanf("%d%c", &nums[i], &space);
       i++;
   }
    
   switch(command){
       case 0:
       index_first_negative(nums, i); break;
       case 1:
       index_last_negative(nums, i); break;
       case 2:
       sum_between_negative(nums, i); break;
       case 3:
       sum_before_and_after_negative(nums, i); break;
       default:
       printf("%s\n", OUTPUT_ERROR_STRING); break;
   }
   return 0;
}