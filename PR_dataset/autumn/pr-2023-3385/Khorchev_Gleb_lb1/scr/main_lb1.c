#include <stdio.h>
#define SIZE 20

int index_first_negative(int* arr, size_t len){
    for(size_t i = 0; i < len; i++)
    {
        if (arr[i] < 0) return i;
    }
}

int index_last_negative(int* arr, size_t len){
    for(size_t i = len-1; i != -1; i--)
    {
        if( arr[i] < 0) return i;
    }
}

int multi_between_negative(int* arr, size_t len){
    size_t ind_f = index_first_negative(arr, len);
    size_t ind_l = index_last_negative(arr, len);
    int mult = 1;
    for(size_t i = ind_f; i < ind_l; i++) mult *= arr[i];
    return mult;
}

int multi_before_and_after_negative(int* arr, size_t len){
    size_t ind_f = index_first_negative(arr, len);
    size_t ind_l = index_last_negative(arr, len);
    int mult = 1;
    for(size_t i = 0; i < ind_f; i++) mult *= arr[i];
    for(size_t i = ind_l; i < len; i++) mult *= arr[i];
    return mult;
}

int main(){
    int arr[SIZE];
    size_t len = 0;
    int a;
    scanf("%d", &a);
    char c = getchar();
    while(1){
        if ( c == '\n') break;
        scanf("%d", &arr[len++]);
        c = getchar();
    }
    switch(a){
        case 0:
            printf("%d", index_first_negative(arr, len));
            break;
        case 1:
            printf("%d", index_last_negative(arr, len));
            break;
        case 2:
            printf("%d", multi_between_negative(arr, len));
            break;
        case 3:
            printf("%d", multi_before_and_after_negative(arr, len));
            break;
        default:
            printf("Данные некорректны");
    }
    return 0;
}