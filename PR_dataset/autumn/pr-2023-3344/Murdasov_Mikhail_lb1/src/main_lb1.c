#include <stdio.h>
#include <stdlib.h>

int index_first_even(int array[], int ind_count){
    int i;
    int index_answer;
    int flag;
    for(i = 0; i<ind_count; i++){
        if(array[i] % 2 == 0){
            index_answer = i;
            flag = 1;
            break;
        }
    }
    
    if(flag != 1){
        puts("Данные некорректны\n");
        return 0;
    }

    return index_answer;
}

int index_last_odd(int array[], int ind_count){
    int i;
    int index_answer;
    int flag;
    for(i = 0; i<ind_count; i++){
        if(array[i] % 2 != 0){
            index_answer = i;
            flag = 1;
        }
    }

    if(flag != 1){
        puts("Данные некорректны\n");
        return 0;
    }

    return index_answer;
}

int sum_between_even_odd(int array[], int ind_count){
    int index_last_odd1 = index_last_odd(array, ind_count);
    int sum_answer = 0;
    for(int index_first_even1 = index_first_even(array, ind_count); index_first_even1 < index_last_odd1; index_first_even1++){
        sum_answer+=abs(array[index_first_even1]);
    }

    return sum_answer;
}

int sum_before_even_and_after_odd(int array[], int ind_count){
    int index_first1 = index_first_even(array, ind_count);
    int sum_answer = 0;
    for(int i = 0; i < index_first1; i++){
        sum_answer+=abs(array[i]);
    }

    for(int index_last_odd1 = index_last_odd(array, ind_count); index_last_odd1 < ind_count; index_last_odd1++){
        sum_answer+=abs(array[index_last_odd1]);
    }

    return sum_answer;
}
int main(){
    int a;
    int i;
    int arr[100];
    int ind_count;

    scanf("%d", &a);

    if(a != 0 && a != 1 && a != 2 && a != 3){
        puts("Данные некорректны\n");
        return 0;
    }
    
    for(i = 0; i<100 && getchar() != '\n'; i++){
        scanf("%d", &arr[i]);
        ind_count = i+1;
    }

    switch(a){
        case 0:
            printf("%d\n", index_first_even(arr, ind_count));
            break;
        case 1:
            printf("%d\n", index_last_odd(arr, ind_count));
            break;
        case 2:
            printf("%d\n", sum_between_even_odd(arr, ind_count));
            break;
        case 3:
            printf("%d\n", sum_before_even_and_after_odd(arr, ind_count));
            break;
        
        default:
            puts("Данные некорректны\n");
            break;
    }

    return 0;
}