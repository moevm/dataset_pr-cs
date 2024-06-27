#include <stdio.h>
#include <stdlib.h>


int index_first_negative(int arr[100]){
    for (int index = 0; index < 100; index++){
        if(arr[index] < 0){
            return index;
        }
    }
}


int index_last_negative(int arr[100]){
    int res;
    for (int index = 99; index >= 0; index--){
        if(arr[index] < 0){
            return index;
        }
    }
    
}


int sum_between_negative(int arr[100]){
    int sum = 0;
    int first_negative = index_first_negative(arr);
    int last_negative = index_last_negative(arr);
    for (int index = first_negative; index < last_negative; index++){
        sum += abs(arr[index]);
    }
    return sum;
}


int sum_before_and_after_negative(int arr[100]){
    int sum = 0;
    int first_negative = index_first_negative(arr);
    int last_negative = index_last_negative(arr);
    for (int index = 0; index < first_negative; index++){
        sum += abs(arr[index]);
    }
    for (int index = last_negative; index < 100; index++){
        sum += abs(arr[index]);
    }
    return sum;
}


int main(){
    int act;
    scanf("%d", &act);
    int arr[100] = {0};
    int index = 0;
    int num;
    do{
        if (scanf("%d", &num) == 1){
            arr[index] = num;
        }
        else{
            printf("Данные некорректны\n");
            return 0;
        }
        index++;  
    } while(getchar()!= '\n' && index < 100);

    switch(act){
        case 0:
            printf("%d\n", index_first_negative(arr));
            break;
        case 1:
            printf("%d\n", index_last_negative(arr));
            break;
        case 2:
            printf("%d\n", sum_between_negative(arr));
            break;
        case 3:
            printf("%d\n", sum_before_and_after_negative(arr));
            break;
        default:
            printf("Данные некорректны\n");
    }

    return 0;
}

