#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"
#define ARRAY_SIZE 20

void input_number(int* number_ptr) {
    scanf("%d", number_ptr);
}

void input_array(int arr[], int* counter_ptr) {
    char symbol = 0;
    do
    {
        scanf("%d%c",&arr[*counter_ptr],&symbol);
        (*counter_ptr)++;
    }
    while(symbol!='\n'); 
}

void switch_case(int arr[], int counter, int number) {
    int calling_first_function,calling_second_function,calling_third_function,calling_fourt_function;
    calling_first_function=index_first_negative(arr);
    calling_second_function=index_last_negative(arr,counter);
    calling_third_function=multi_between_negative(arr,counter,calling_first_function,calling_second_function);
    calling_fourt_function=multi_before_and_after_negative(arr,counter,calling_first_function,calling_second_function);
    switch(number){
        case 0:
            printf("%d",calling_first_function);
            break;
        case 1:
            printf("%d",calling_second_function);
            break;
        case 2:
            printf("%d",calling_third_function);
            break;
        case 3:
            printf("%d",calling_fourt_function);
            break;
        default:
            printf("Данные некорректны");
    }
}

int main()
{
    int number;
    input_number(&number);

    int arr[ARRAY_SIZE];
    
    int counter = 0;
    input_array(arr, &counter);
    
    switch_case(arr, counter, number);
    
    
    return 0;
}