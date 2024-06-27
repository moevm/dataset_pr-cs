#include <stdio.h>
#include <stdlib.h>

int index_first_even(int arr[], int len){
    
    for(int i = 0; i < len; i++){
        if(abs(arr[i]) % 2 == 0){
            return i;
            break;
        }
    }
}

int index_last_odd(int arr[], int len){
    
    int r;
    
    for(int i = 0; i < len; i++){
        if(abs(arr[i]) % 2 == 1){
            r = i;
        }
    }
    return r;
}

int sum_between_even_odd(int f, int l, int arr[]){

    int sum = 0;
    
    for(int i = f; i < l; i++){
        sum += abs(arr[i]);
    }
    return sum;
}

int sum_before_even_and_after_odd(int first, int last, int len, int arr[]){

    int sum = 0;

    for(int i = 0; i < len; i++){
        if((i < first) || (i >= last)){
            sum += abs(arr[i]);
        }
    }
    return sum;
}

int main(){

    int len,x,arr[100];
    int i = 0;
    char space;

    scanf("%d%c", &x, &space);
    do {
        scanf("%d%c", &arr[i], &space);
        i += 1;
    } while (space != '\n');
    len = i;

    int first = index_first_even(arr, len);
    int last = index_last_odd(arr, len);
    int sum1 = sum_between_even_odd(first, last, arr);
    int sum2 = sum_before_even_and_after_odd(first, last, len, arr);

    switch(x){
        case 0:
            printf("%d\n", first);
            break;
        case 1:
            printf("%d\n", last);
            break;
        case 2:
            printf("%d\n", sum1);
            break;
        case 3:
            printf("%d\n", sum2);
            break;
        default:
            printf("Данные некорректны\n");
  }
  return 0;
}