#include <stdio.h>
#include <stdlib.h>
#define N 100
#define ERR -1
#define OUTPUT_ERR "Данные некорректны"

int index_first_zero(int arr[], int len_arr){
    int index = ERR;
    for (int j = 0; j < len_arr; j++){
        if (arr[j] == 0){
            index = j;
            break;
        }
    }
    return index;
}

int index_last_zero(int arr[], int len_arr){
    int index = ERR;
    for (int j = len_arr; j > 0; j--){
        if (arr[j-1] == 0){
            index = j-1;
            break;
        }
    }
    return index;
}

int sum_between(int arr[], int len_arr){
    int first = index_first_zero(arr,len_arr);
    int last = index_last_zero(arr,len_arr);
    int sum = 0;
    if ((first == ERR) || (last == ERR)){
        sum = ERR;
    }
    else{
        for (int j = first; j < last; j++){
            sum = sum + abs(arr[j]);
        }
    }
    return sum;
}

int sum_before_and_after(int arr[], int len_arr){
    int first = index_first_zero(arr,len_arr);
    int last = index_last_zero(arr,len_arr);
    int sum = 0;
    if ((first == ERR ) || (last == ERR)){
        sum = ERR;
    }
    else{
        for (int j = 0; j < first; j++){
            sum = sum + abs(arr[j]);
        }
        for (int j = last; j < len_arr; j++){
            sum = sum + abs(arr[j]);
        }
    }
    return sum;
}

int main(void) {
    int chisla[N] = {0};
    int len = 0;
    int i = 0;
    int variant = 0;
    scanf("%d", &variant);
    do {
        scanf("%d", &chisla[i]);
        i++;
        len++;
    }
    while (getchar() != '\n');

    switch(variant){
        case 0:
            if (index_first_zero(chisla,len) == ERR){
                printf("%s\n", OUTPUT_ERR );
            }
            else{
                printf("%d\n", index_first_zero(chisla,len));
            }
            break;
        case 1:
            if (index_last_zero(chisla,len) == ERR){
                printf("%s\n", OUTPUT_ERR );
            }
            else{
                printf("%d\n", index_last_zero(chisla,len));
            }
            break;
        case 2:
            if (sum_between(chisla, len) == ERR){
                printf("%s\n", OUTPUT_ERR );
            }
            else{
                printf("%d\n", sum_between(chisla, len));
            }
            break;
        case 3:
            if (sum_before_and_after(chisla, len) == ERR){
                printf("%s\n", OUTPUT_ERR );
            }
            else{
                printf("%d\n", sum_before_and_after(chisla, len));
            }
            break;
        default:
            printf("%s\n", OUTPUT_ERR );
    }
    return 0;
}
