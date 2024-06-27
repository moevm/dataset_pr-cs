#include <stdio.h>
#include <stdlib.h>
int index_first_zero(int arr[], int len_arr){
    for (int i = 0; i < len_arr; ++i){
        if (arr[i] == 0){
            return i;
        }
    }
    return -1;
}

int index_last_zero(int arr[], int len_arr){
    for (int i = len_arr - 1; i >= 0; --i){
        if (arr[i] == 0){
            return i;
        }
    }
    return -1;
}

int sum_between(int arr[], int len_arr){
    int ans = 0;
    for (int i = index_first_zero(arr, len_arr); i < index_last_zero(arr, len_arr); ++i){
        ans = ans + abs(arr[i]);
    }
    return ans;
}

int sum_before_and_after(int arr[], int len_arr){
    int ans = 0;
    for (int i = 0; i < index_first_zero(arr, len_arr); ++i){
        ans = ans + abs(arr[i]);
    }
    for (int x = index_last_zero(arr,len_arr) + 1; x < len_arr; ++x){
        ans = ans + abs(arr[x]);
    }
    return ans;
}

int main(){
    int num;
    int i = 0;
    int arr[101];
    scanf("%d", &num);
    while (getchar() != '\n'){
        scanf("%d", &arr[i]);
        i++;
    }
    switch(num){
        case 0:
            printf("%d\n", index_first_zero(arr, i));
            break;
        case 1:
            printf("%d\n", index_last_zero(arr, i));
            break;
        case 2:
            printf("%d\n", sum_between(arr, i));
            break;
        case 3:
            printf("%d\n", sum_before_and_after(arr, i));
            break;
        default:
            printf("Данные некорректны");
            break;
    }
}
