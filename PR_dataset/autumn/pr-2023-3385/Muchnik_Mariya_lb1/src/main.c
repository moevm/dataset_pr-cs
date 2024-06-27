#include <stdio.h>
#include <stdlib.h>

int index_first_zero(int arr[], int len)
{
    for(int i = 0; i < len; i++){
        if(arr[i] == 0){
            return i;
        }
    }
}

int index_last_zero(int arr[], int len)
{
    for(int i = len-1; i >= 0; i--){
        if(arr[i] == 0){
            return i;
        }
    }
}

int sum_between(int arr[], int len)
{
    int sum = 0;
    int a = index_first_zero(arr, len), b = index_last_zero(arr, len);
    for(int i = a+1; i < b; i++){
        sum += abs(arr[i]);
    }
    return sum;
}

int sum_before_and_after(int arr[], int len)
{
    int sum = 0;
    for(int i = 0; i < len; i++){
        sum += abs(arr[i]);
    }
    return sum - sum_between(arr, len);
}

int main()
{
    int n, arr[100], len = 0;
    char c;
    
    scanf("%d", &n);
    
    do {
        scanf("%d", &arr[len]);
        len++;
    } while(c = getchar() != '\n');
    
    switch(n){
        case 0:
            printf("%d\n", index_first_zero(arr, len));
            break;
        case 1:
            printf("%d\n", index_last_zero(arr, len));
            break;
        case 2:
            printf("%d\n", sum_between(arr, len));
            break;
        case 3:
            printf("%d\n", sum_before_and_after(arr, len));
            break;
        default:
            printf("Данные некорректны");
    }
}