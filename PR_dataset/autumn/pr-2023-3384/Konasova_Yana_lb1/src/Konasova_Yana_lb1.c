#include <stdio.h>
#include <stdlib.h>

int abs_max(int arr[], int len) {
    int max = abs(arr[0]);
    int rez=arr[0];
    for (int i = 1; i < len; i++) {
        int absValue = abs(arr[i]);
        if (absValue > max) {
            max = absValue;
            rez=arr[i];
        }
    }
    return rez;
}
int abs_min(int arr[], int len) {
    int min = abs(arr[0]);
    int rez = arr[0];
    for (int i = 1; i < len; i++) {
        int absValue = abs(arr[i]);
        if (absValue < min) {
            min = absValue;
            rez=arr[i];
        }
    }
    return rez;
}
int diff(int arr[], int len) {
    int max = abs_max(arr, len);
    int min = abs_min(arr, len);
    int rez=max-min;
    return rez;
}
int sum(int arr[], int len) {
    int max_val = abs_max(arr, len);
    int max_index = -1;
    for (int i = 0; i < len; i++) {
        if (arr[i] == max_val) {
            max_index = i;
            break;
        }
    }

    int sumi = 0;
    for (int i = max_index; i < len; i++) {
        sumi += arr[i];
    }

    return sumi;
}
int main() {
    int a;
    scanf("%d", &a);
    int len =0;
    int arr[100];
    char g;
    while (len < 100){
        scanf("%d%c", &arr[len], &g);
        if (g=='\n'){
            len++;
            break;
        }else{
            len++;
        }
                
    }
    
    switch (a) {
            case 0:
                printf("%d\n", abs_max(arr, len));
                break;
            case 1:
                printf("%d\n", abs_min(arr, len));
                break;
            case 2:
                printf("%d\n", diff(arr, len));
                break;
            case 3:
                printf("%d\n", sum(arr, len));
                break;
            default:
                printf("Данные некорректны\n");
        }
    

    return 0;
}
