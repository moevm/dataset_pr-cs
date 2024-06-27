#include <stdio.h>
#include <stdlib.h>

#define MAX_ARRAY_SIZE 100

int abs_max(int array_num[], int length) {
    int max_num = 0;
    int answer = 0;

    for (int i = 0; i < length; i++) {
        if(abs(array_num[i]) > max_num ){
            max_num = abs(array_num[i]);
            answer = array_num[i];
        }
    }
    return answer;
}

int abs_min(int array_num[], int length) {
    int answer = array_num[0];
    int min_num = abs(array_num[0]);

    for (int i = 0; i < length; i++) {
        if (abs(array_num[i]) < min_num) {
            min_num = abs(array_num[i]);
            answer = array_num[i];
        }
    }
    return answer;
}

int diff(int array_num[], int length){
    return abs_max(array_num, length) - abs_min(array_num, length);
}

int sum(int array_num[], int length){
    int max_num = abs_max(array_num, length);
    int sum = 0;

    for (int i = 0; i < length; i++) {
        if(max_num == array_num[i]){
            for (int j = i; j < length; j++) {
                sum += array_num[j];
            }
            return sum;
        }
    }
}

int main(){
    int choice;
    int array[MAX_ARRAY_SIZE];
    char symbol;

    scanf("%d", &choice);

    int i = 0;
    do{
        scanf("%d%c", &array[i], &symbol);
        i++;
    } while(symbol != '\n' && i < 100);
    int array_length = i;


    switch (choice) {
        case 0:
            printf("%d\n", abs_max(array, array_length));
            break;
        case 1:
            printf("%d\n", abs_min(array, array_length));
            break;
        case 2:
            printf("%d\n", diff(array, array_length));
            break;
        case 3:
            printf("%d\n", sum(array, array_length));
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }

    return 0;
}