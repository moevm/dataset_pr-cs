#include <stdio.h>
int max_number(int arr[], int n){
    int max = 0;
    for(int i=1;i<n;i++){
        if (arr[i]>max)
        max = arr[i];
    }
    return max;
}
int min_number(int arr[], int n){
    int min = 1000000;
    for(int i=1;i<n;i++){
        if (arr[i]<min)
        min = arr[i];
    }
    return min;
}
int diff(int arr[], int n){
    return max_number(arr, n)-min_number(arr, n);
}
int sum_numbers(int arr[], int n){
    int sum = 0;
    for(int i=0;arr[i]!=min_number(arr, n) && i<n;i++){
        sum += arr[i];
    }
    return sum;
}
int main(){
    int selection;
    scanf("%d", &selection);
    int arr[200];
    int quantity;
    for(int i = 0;i<200;i++){
        char letter;
        scanf("%d%c", &arr[i], &letter);
        if(letter == '\n'){
            quantity = i;
            break;
        }
    }
    switch(selection){
        case 0:
            printf("%d\n",max_number(arr, quantity));
            break;
        case 1:
            printf("%d\n",min_number(arr, quantity));
            break;
        case 2:
            printf("%d\n",diff(arr, quantity));
            break;
        case 3:
            printf("%d\n",sum_numbers(arr, quantity));
            break;
        default: 
            printf("Данные некорректны\n");
    }
        return 0;
}