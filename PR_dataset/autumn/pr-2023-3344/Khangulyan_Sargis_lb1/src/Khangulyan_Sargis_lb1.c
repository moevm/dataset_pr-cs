#include <stdio.h>
#include <stdlib.h>

int abs_max(int arr[], int arrsize, int r){
    int max = 0; 
    int maxindex, i;
    for (i = 0; i < arrsize; i++){
        if (abs(arr[i]) > abs(max)){
            max = arr[i];
            maxindex = i;
        }
    }
    if (r){
        return max;
    }
    else{
        return maxindex;
    }
}

int abs_min(int arr[], int arrsize){
    int min = arr[0]; 
    int i;
    for (i = 0; i < arrsize; i++){
        if (abs(arr[i]) < abs(min)){
            min = arr[i];
        }
    }
    return min;
}

int diff(int max, int min){
    int df = max - min;
    return df;
}

int sum(int arr[], int arrsize){
    int sum = 0;
    int i;
    for (i = abs_max(arr, arrsize, 0); i < arrsize; i++){
        sum += arr[i];
    }
    return sum;
}

int main(){
    int arr[100], r;
    int arrsize = 0;
    scanf("%d", &r);
    while(getchar() != '\n'){
        scanf("%d", &arr[arrsize]);
        arrsize++;
    }
    if ((arrsize > 100) || (arrsize <= 0)){
        printf("Данные некорректны\n");
        return 0;
    }
    else{
        switch(r){
            case 0:
                printf("%d\n", abs_max(arr, arrsize, 1));
                break;
            case 1:
                printf("%d\n", abs_min(arr, arrsize));
                break;
            case 2:
                printf("%d\n", diff(abs_max(arr, arrsize, 1), abs_min(arr, arrsize)));
                break;
            case 3:
                printf("%d\n", sum(arr, arrsize));
                break;
            default:
                printf("Данные некорректны\n");
                break;
        }
    }
    return 0;
}