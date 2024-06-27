#include <stdio.h> 
#include <stdlib.h> 
#define MAX_SIZE 100


int input_arr(int numbers[], int max_size)
{
    char space = ' ';
    int size = 0;

    while (size < max_size && space != '\n'){
        scanf("%d%c", &numbers[size], &space);
        size++;
    }

    return size;
}


int sum_arr(const int numbers[], int left_border, int right_border)
{
    int sum_abs = 0;
    for(int i = left_border; i < right_border; i++)
        sum_abs = sum_abs + abs(numbers[i]);

    return sum_abs;
}


int index_first_zero(const int numbers[], int size_arr)
{
    int index_first = 0;
    for (int i = 0; i < size_arr; i++){
        if (numbers[i] == 0){
            index_first = i;
            break;
        }
    }
    return index_first;
}


int index_last_zero(const int numbers[], int size_arr)
{
    int index_last = 0; 
    for (int i = size_arr-1; i >= 0; i--){
        if (numbers[i] == 0){
            index_last = i;
            break;
        }
    }
    return index_last;
}


int sum_between(const int numbers[], int size_arr)
{
    int index_first = index_first_zero(numbers, size_arr);
    int index_last = index_last_zero (numbers, size_arr);
    int sum_b = sum_arr(numbers, index_first, index_last); 

    return sum_b;
}


int sum_before_and_after(const int numbers[], int size_arr)
{
    int index_first = index_first_zero(numbers, size_arr);
    int index_last = index_last_zero (numbers, size_arr);
    int sum_b_and_a = sum_arr(numbers, 0, index_first) + sum_arr(numbers, index_last, size_arr);

    return sum_b_and_a;
}


void menu_output(const int arr[], int size_arr, int item)
{
    switch (item)
    {
    case 0:
        printf("%d\n", index_first_zero(arr, size_arr));
        break;

    case 1:
        printf("%d\n", index_last_zero(arr, size_arr));
        break;

    case 2:
        printf("%d\n", sum_between(arr, size_arr));
        break;
        
    case 3:
        printf("%d\n", sum_before_and_after(arr, size_arr));
        break;            
    
    default:
    printf("Данные некорректны\n");
        break;
    }
}

int main() {

    int item = 0, size_arr = 0;
    int arr[MAX_SIZE]; 
    
    scanf("%d ", &item);

    size_arr = input_arr(arr, MAX_SIZE);
    menu_output(arr, size_arr, item);

    return 0; 
}