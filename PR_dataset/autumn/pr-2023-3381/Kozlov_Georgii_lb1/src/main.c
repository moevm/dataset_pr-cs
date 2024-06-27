#include <stdio.h>


int max(int array[100], int len){
    int max = array[0];
    for (int i = 0; i < len; i++){
        if (array[i] > max){
            max = array[i];
        }
    }
    return max;
}

int min(int array[100], int len){
    int min = array[0];
    for (int i = 0; i < len; i++){
        if (array[i] < min){
            min = array[i];
        }
    }
    return min;
}

int diff(int array[100], int len){
    return max(array, len) - min(array, len);
}

int sum(int array[100], int len){
    int min_num = min(array, len);
    int summ = 0;
    for (int i = 0; i < len; i++){
        if (array[i] == min_num){
            break;
        }
        summ += array[i];
    }
    return summ;
}

int main(){
    int array[100];
    int number;
    int command;
    int len = 0;
    scanf("%d", &command);
    while (getchar() != '\n'){
        scanf("%d", &number);
        array[len] = number;
        len++;
    }
    
    switch (command){
    case 0:
        printf("%d\n", max(array, len));
        break;
    case 1:
        printf("%d\n", min(array, len));
        break;
    case 2:
        printf("%d\n", diff(array, len));
        break;
    case 3:
        printf("%d\n", sum(array, len));
        break;
    default:
        printf("Данные некорректны\n");
    }
    return 0;
}