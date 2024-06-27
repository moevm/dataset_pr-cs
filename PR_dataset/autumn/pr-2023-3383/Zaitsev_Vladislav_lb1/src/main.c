#include <stdlib.h>
#include <stdio.h>
#define N 100
int index_first_even(int arr[],int len){
    for (int i = 0; i < len; i++){
        if (arr[i] % 2 == 0){
            return i;
            break;
        }
    }    
}
int index_last_odd(int arr[], int len){
    int answer = 0;
    for (int i = 0; i < len; i++){
        if (arr[i] % 2 != 0){
            answer = i;
        }        
    }
    return answer;
}
int sum_between_even_odd(int arr[], int len){
    int answer = 0;
    for (int i = index_first_even(arr, len); i < index_last_odd(arr, len); i++){
            answer = answer + abs(arr[i]);        
        }
    return answer;
}
int sum_before_even_and_after_odd(int arr[], int len){
    int answer = 0;
    for (int i = 0; i < index_first_even(arr, len); i++){
        answer = answer + abs(arr[i]);
    }
    for (int i = index_last_odd(arr, len); i < len; i++){
        answer = answer + abs(arr[i]);
    }
    return answer;
}
int main()
{
    int opperation, len = 0;
    int arr[N];
    char end_l; 
    scanf("%d%c", &opperation, &end_l);
    while (end_l != '\n'){
        scanf("%d%c", &arr[len], &end_l);
        len++;
    }
    switch (opperation){
        case 0:
            printf("%d\n", index_first_even(arr, len));
            break;
        case 1:
            printf("%d\n", index_last_odd(arr, len));
            break;
        case 2:
            printf("%d\n", sum_between_even_odd(arr, len));
            break;
        case 3:
            printf("%d\n", sum_before_even_and_after_odd(arr, len));
            break;
        default:
            printf("Данные некорректны\n");
    }
    return 0;
}
