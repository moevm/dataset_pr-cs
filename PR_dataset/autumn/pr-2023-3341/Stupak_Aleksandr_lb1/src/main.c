#include <stdio.h>
#define N 20

int index_first_negative(int arr[], int i) {
    for (int k = 0; k < i; k++) {
        if (arr[k] < 0) {
            return k;
        }
    }
}

int index_last_negative(int arr[], int i) {
    for(int k = i - 1; k >= 0; k--) {
        if(arr[k] < 0){
            return k;
        }
    }
}

int multi_between_negative(int arr[], int i) {
    int multi = 1;
    for(int k = index_first_negative(arr, i); k < index_last_negative(arr, i); k++){
        multi *= arr[k];
    }
    return multi;
}

int multi_before_and_after_negative(int arr[], int i) {
    int multi = 1;
    for(int k = 0; k < index_first_negative(arr, i); k++){
        multi *= arr[k];
    }
    for(int k = index_last_negative(arr, i); k < i; k++){
        multi *= arr[k];
    }
    return multi;
}

int main() {
    int funk_id = 0;
    int arr[N];
    int i = 0;
    char space = ' ';
    scanf("%d", &funk_id);
    while (i < N && space == ' ') {
        scanf("%d%c", &arr[i], &space);
        i++;
    }
    switch (funk_id) {
        case 0:
            printf("%d\n", index_first_negative(arr, i));
            break;
        case 1:
            printf("%d\n", index_last_negative(arr, i));
            break;
        case 2:
            printf("%d\n", multi_between_negative(arr, i));
            break;
        case 3:
            printf("%d\n", multi_before_and_after_negative(arr, i));
            break;
        default:
            printf("Данные некорректны");

    }
    return 0;
}
