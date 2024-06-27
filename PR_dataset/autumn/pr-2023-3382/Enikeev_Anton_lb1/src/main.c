#include <stdio.h>
#include <limits.h>

#define SIZE 100


int max(int arr[], int arr_len);
int min(int arr[], int arr_len);
int diff(int arr[], int arr_len);
int sum(int arr[], int arr_len);

int main()
{
    int number, arr[SIZE], i = 0, result;
    char end_line;
    scanf("%d", &number);
    do{
        scanf("%d%c", &arr[i], &end_line);
        i++;
    }while (end_line != '\n' && i < SIZE);
    int arr_len = i;
    switch (number){
        case 0:
            result = max(arr, arr_len);
            printf("%d\n", result);
            break;
        case 1:
            result = min(arr, arr_len);
            printf("%d\n", result);
            break;
        case 2:
            result = diff(arr, arr_len);  
            printf("%d\n", result);
            break;
        case 3:
            result = sum(arr, arr_len);
            printf("%d\n", result);
            break;
        default:
            printf("Данные некорректны");
    } 
    return 0;
}

int max(int arr[], int arr_len)
{
    int max_res = INT_MIN, i;
    for (i = 0; i < arr_len; i++){
        if (arr[i] > max_res){
            max_res = arr[i];
        }
    }
    return max_res;
}

int min(int arr[], int arr_len)
{
    int min_res = INT_MAX, i;
    for (i = 0; i < arr_len; i++){
        if (arr[i] < min_res){
            min_res = arr[i];
            }
    }
    return min_res;
}

int diff(int arr[], int arr_len)
{
    int diff_res;
    diff_res = max(arr, arr_len) - min(arr, arr_len);
    return diff_res;
}




int sum(int arr[], int arr_len)
{
    int res_sum = 0, i;
    int min_element = min(arr, arr_len);
    
    for (i = 0; i < arr_len; i++){
        if (arr[i] == min_element){
            break;
        }
        res_sum += arr[i];
    }
    return res_sum;
}

