#include <stdio.h>

int index_first_negative(int * array, int len_array) {
    int i;
    for (i = 0; i < len_array; i ++) {
        if (array[i] < 0) {
            return i;
        }
    }
}

int index_last_negative(int * array, int len_array) {
    int i;
    for (i = len_array - 1; i > 0; i --) {
        if (array[i] < 0){
            return i;
        }
    }
}

long long int multi_between_negative(int * array, int len_array) {
    int i;
    long long int multi = 1;
    int start = index_first_negative(array, len_array);
    int finish = index_last_negative(array, len_array);
    for (i = start; i < finish; i ++) {
        multi *= array[i];
    }
    return multi;
}

long long int multi_before_and_after_negative(int * array, int len_array) {
    int i;
    long long int multi = 1;
    int finish = index_first_negative(array, len_array);
    int start = index_last_negative(array, len_array);
    for (i = 0; i < finish; i ++) {
        multi *= array[i];
    }
    for (i = start; i < len_array; i ++) {
        multi *= array[i];
    }
    return multi;
}

int main()
{
    int array[100];
    int task = -1, len_array = 0;
    long long int answer;
    char symbol;
    scanf("%d%c", &task, &symbol);
    if (task < 0 || task > 3) {
        printf("Данные некорректны\n");
        return 0;
    }
    symbol = 'a';
    
    do {
        scanf("%d%c", &array[len_array], &symbol);
        len_array ++;
    } while (symbol != '\n');
    
    switch(task) {
        case 0:
            answer = index_first_negative(array, len_array);
            break;
        case 1:
            answer = index_last_negative(array, len_array);
            break;
        case 2:
            answer = multi_between_negative(array, len_array);
            break;
        case 3:
            answer = multi_before_and_after_negative(array, len_array);
            break;
    }
    printf("%lld\n", answer);

    return 0;
}
