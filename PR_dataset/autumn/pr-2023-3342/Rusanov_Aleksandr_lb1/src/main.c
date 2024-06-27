#include <stdio.h>
#include <stdlib.h>
#define N 100

int abs_max(int arr[], int size, int flag){
    int result = arr[0];
    int index = 0;
    for (int i = 1; i < size; i++){
        if (abs(arr[i]) > (abs(result))){
            result = arr[i];
            index = i;
        }
    }
    if (flag == 1){
        return result;
    }
    else{
        return index;
        }

}

int abs_min(int arr[], int size){
    int result = arr[0];
    for (int i = 1; i < size; i++){
        if ((abs(arr[i])) < (abs(result))){
            result = arr[i];
        }
    }
    return result;
}

int diff(int arr[], int size){
    int result = abs_max(arr, size, 1) - abs_min(arr, size);
    return result;
}

int sum(int arr[], int size, int index){
    int sum = 0;
    for (int k = index; k < size; k++ ){
        sum += arr[k];
    }
    return sum;
}


int main(){
    int flag;
    int size = 0;
    int arr[N];
    scanf("%d", &flag);
    while(getchar() != '\n'){
        scanf("%d",&arr[size]);
        size++;}


    switch(flag){
        case 0:
            printf("%d\n", abs_max(arr, size, 1));
            break;
        case 1:
            printf("%d\n", abs_min(arr, size));
            break;
        case 2:
            printf("%d\n", diff(arr, size));
            break;
        case 3: ;
            int index = abs_max(arr, size, 2);
            printf("%d\n", sum(arr, size, index));
            break;
        default:
            printf("Данные некорректны");
    }
    return 0;
}