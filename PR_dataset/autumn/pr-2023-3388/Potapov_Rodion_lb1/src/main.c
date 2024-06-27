#include <stdio.h>
#include <stdlib.h>

int index_first_negative(int* array, int number_of_elements){
    for (int i = 0; i<number_of_elements;i++){
        if (array[i]<0)
        return i;
    }
}

int index_last_negative(int* array, int number_of_elements){
    for (int i = number_of_elements -1 ; i>=0;i--){
        if (array[i] <0)
        return i;
    }
}

int sum_between_negative(int* array, int number_of_elements){
    int index_first = index_first_negative(array, number_of_elements);
    int index_last = index_last_negative(array, number_of_elements);
    
    int sum = 0;
    for (int i = index_first; i<index_last; i++){
        sum+= abs(array[i]);
    }
    return sum;
}

int sum_before_and_after_negative(int* array, int number_of_elements){
    int index_first = index_first_negative(array, number_of_elements);
    int index_last = index_last_negative(array, number_of_elements);
    
    int sum =0;
    for (int i = 0; i< index_first; i++){
        sum += abs(array[i]);
    }
    for (int i = index_last; i < number_of_elements; i++){
        sum += abs(array[i]);
    }
    return sum;
}

int main(void){
    int answer = 0;
    
    int num=100;
    int arr[num];
    int number=0;
    char check;
    
    int key;
    scanf("%d%c", &key, &check);
    while(check!='\n' && number<num){
        scanf("%d%c", &arr[number], &check);
        number++;
    }
    
    switch ( key){
        case 0:
            answer = index_first_negative(arr, number);
            break;
        case 1:
            answer = index_last_negative(arr, number);
            break;
        case 2:
            answer = sum_between_negative(arr, number);
            break;
        case 3:
            answer = sum_before_and_after_negative(arr, number);
            break;
        default:
            puts("Данные некорректны");
            return 0;
    }
    printf("%d\n", answer);
    return 0;
}