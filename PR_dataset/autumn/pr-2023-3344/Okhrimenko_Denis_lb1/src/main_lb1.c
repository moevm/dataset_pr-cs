#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE_OF_ARRAY 100


int abs_max(int arr[], int count)
{
    int maxim_abs = -1;
    int maxim_ind = 0;
    for(int i = 0; i < count; ++i){
        if(maxim_abs < abs(arr[i])){
            maxim_abs = abs(arr[i]);
            maxim_ind = i;
        }
    }
    return arr[maxim_ind];
}

int abs_min(int arr[], int count)
{
    int minim_abs = abs(arr[0]);
    int minim_ind = 0;
    for(int i = 1; i < count; ++i){
        if(minim_abs > abs(arr[i])){
            minim_abs = abs(arr[i]);
            minim_ind = i;
        }
    }
    return arr[minim_ind];
}

int diff(int arr[], int count)
{
    int result_abs_max = abs_max(arr, count);
    int result_abs_min = abs_min(arr, count);
    int difference = result_abs_max - result_abs_min;
    return difference;
}

int sum(int arr[], int count)
{
    int maxim = abs_max(arr, count);
    int flag = 0;
    int summa = 0;
    for(int i = 0; i < count; ++i){
        if(flag == 0){
            if(maxim == arr[i]){
                flag = 1;
                summa += arr[i];
            }
        } else {
            summa += arr[i];
        }
    }
    return summa;
}

int main()
{
    int ans;
    int count = 0;
    char c = ' ';
    int arr[MAX_SIZE_OF_ARRAY];
    int check;
    scanf("%d", &check);

    while(getchar() != '\n'){
        scanf("%d", &arr[count++]);
    }

    switch (check){
        case 0:
            ans = abs_max(arr, count);
            printf("%d\n", ans);
            break;
        case 1:
            ans = abs_min(arr, count);
            printf("%d\n", ans);
            break;
        case 2:
            ans = diff(arr, count);
            printf("%d\n", ans);
            break;
        case 3:
            ans = sum(arr, count);
            printf("%d\n", ans);
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }
    return 0;
}
