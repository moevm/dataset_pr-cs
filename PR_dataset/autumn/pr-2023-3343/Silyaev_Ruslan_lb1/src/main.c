#include <stdio.h>
#include <stdlib.h>

int array[101];
int sizeOfArray = 0, func;

int index_first_even(int array[sizeOfArray]){
    for(int i = 0; i < sizeOfArray; ++i){
        if(array[i]%2==0){
            return i;
        }   
    }
}

int index_last_odd(int array[sizeOfArray]){
    for(int i = 0; i < sizeOfArray; i++){
        if(array[sizeOfArray-i]%2!=0){
            return sizeOfArray-i;
        }
    }
}

int sum_between_even_odd(int array[sizeOfArray]){
    int sumOfArray = 0;
    for(int i = index_first_even(array); i < index_last_odd(array); i++){
        sumOfArray += abs(array[i]);
    }
    return sumOfArray;
}

int sum_before_even_and_after_odd(int array[sizeOfArray]){
    int sumOfArray = 0;
    for(int i = 0; i < sizeOfArray; i++){
        if ((i < index_first_even(array)) || (i >= index_last_odd(array))) 
            sumOfArray += abs(array[i]);
    }
    return sumOfArray;
}

int main(){
    scanf("%d", & func);
    while(getchar() != '\n'){
        scanf("%d", & array[sizeOfArray]);
        ++sizeOfArray;
    }
    switch(func){
        case 0:
            printf("%d", index_first_even(array));
            break;
        case 1:
            printf("%d", index_last_odd(array));
            break;
        case 2:
            printf("%d", sum_between_even_odd(array));
            break;
        case 3:
            printf("%d", sum_before_even_and_after_odd(array));
            break;
        default:
            puts("Данные некорректны");
    }
}
