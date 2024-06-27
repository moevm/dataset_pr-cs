#include <stdio.h>
#include <stdlib.h>

int index_first_negative(int array[], int count){
    for(int i = 0; i<count; i++){
        if (array[i]<0){
            return i;
            break;
        }
    }
}

int index_last_negative(int array[], int count){
    for(int i = count-1; i>-1; i--){
        if(array[i]<0){
            return i;
            break;
        }
    }
}

int sum_between_negative(int array[], int count){
    int sum_b_n = 0;
    for(int i = index_first_negative(array, count); i<index_last_negative(array, count); i++){
        sum_b_n += abs(array[i]);
    }
    return sum_b_n;
}

int sum_before_and_after_negative(int array[], int count){
    int sum_b_a_n = 0;
    for(int i = 0; i<index_first_negative(array, count); i++){
        sum_b_a_n+= abs(array[i]);
    }
    for(int i = index_last_negative(array, count); i<count; i++){
        sum_b_a_n+= abs(array[i]);
    }
    return sum_b_a_n;
}


int main(){
    int array[100];
    int x;
    int count = 0;
    scanf("%d", &x);
    do {
        scanf("%d", &array[count++]);
    } while(getchar() != '\n');
    switch (x) {
        case 0:
            printf("%d\n", index_first_negative(array, count));
            break;
        case 1:
            printf("%d\n", index_last_negative(array, count));
            break;
        case 2:
            printf("%d\n", sum_between_negative(array, count));
            break;
        case 3:
            printf("%d\n", sum_before_and_after_negative(array, count));
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }
    return 0;
}
