#include <stdio.h>
int index_first_negative(int arr[],int n) {
    int res = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) {
            res = i;
            break;
        }
    }
    return res;
}
int index_last_negative(int arr[],int n) {
    int res = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) {
            res = i;
        }
    }
    return res;
}
int multi_between_negative(int arr[],int n) {
    int mul = 1;
    for (int i = index_first_negative(arr, n); i < index_last_negative(arr,n); i++) {
        mul = mul * arr[i];
    }
    return mul;
}
int multi_before_and_after_negative(int arr[],int n){
    int mul = 1;
    for (int i = 0; i < index_first_negative(arr, n); i++) {
        mul = mul * arr[i];
    }
    for (int i = index_last_negative(arr,n); i < n; i++){
        mul = mul * arr[i];
    }
    return mul;
}
int main()
{
    int n = 0;
    int menu;
    scanf("%d", &menu);
    int arr[20];
    while(n < 20){
        scanf("%d", &arr[n]);
        n++;
        if (getchar() == '\n'){
            break;
        }
    }
    switch (menu) {
        case 0:
            printf("%d\n", index_first_negative(arr,n));
            break;
        case 1:
            printf("%d\n", index_last_negative(arr,n));
            break;
        case 2:
            printf("%d\n", multi_between_negative(arr,n));
            break;
        case 3:
            printf("%d\n", multi_before_and_after_negative(arr,n));
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }
    return 0;
}
