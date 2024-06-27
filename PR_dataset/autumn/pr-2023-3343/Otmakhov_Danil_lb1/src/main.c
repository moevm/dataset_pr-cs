#include <stdio.h>
int arr[20];

int index_first_negative(int arr[], int sizeOfArr){
    int index_first;
    int i = 0;
    while (i < sizeOfArr){
        if (arr[i] < 0){
            index_first = i;
            break;
        }
        i++;
    }
    return index_first;
}

int index_last_negative(int arr[], int sizeOfArr){
    int index_last;
    int i = sizeOfArr - 1;
    while (i > 0){
        if (arr[i] < 0){
            index_last = i;
            break;
        }
        i--;
    }
    return index_last;
}

int multi_between_negative(int arr[], int sizeOfArr){
    int product_1 = 1;
    for (int i = index_first_negative(arr, sizeOfArr); i < index_last_negative(arr, sizeOfArr); i++){
        product_1 = product_1 * arr[i];
    }
    return product_1;
}

int multi_before_and_after_negative(int arr[], int sizeOfArr){
    int product_2 = 1;
    int i = 0;
    while (i < index_first_negative(arr, sizeOfArr)){
        product_2 = product_2 * arr[i];
        i++;
    }
    i = index_last_negative(arr, sizeOfArr);
    while (i < sizeOfArr){
        product_2 = product_2 * arr[i];
        i++;
    }
    return product_2;
}

int main(){
    int counterSizeOfArr = 0;
    int command;
    int sizeOfArr;
    scanf("%d", &command);
    while (getchar() != '\n'){
        scanf("%d", &arr[counterSizeOfArr]);
        counterSizeOfArr++;
    }
    sizeOfArr = counterSizeOfArr;
    switch(command){
        case 0: printf("%d\n", index_first_negative(arr, sizeOfArr));
                break;
        case 1: printf("%d\n", index_last_negative(arr, sizeOfArr));
                break;
        case 2: printf("%d\n", multi_between_negative(arr, sizeOfArr));
                break;
        case 3: printf("%d\n", multi_before_and_after_negative(arr, sizeOfArr));
                break;
        default: printf("Данные некорректны\n");
    }
    return 0;
}
