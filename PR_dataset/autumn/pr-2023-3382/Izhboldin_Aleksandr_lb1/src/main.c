#include <stdio.h>
#include <stdlib.h>

int index_first_even(int last_id, long long array[]){
    for (int i = 0; i <= last_id; i++)
        if (array[i]%2 == 0)
            return i;
}

int index_last_odd(int last_id, long long array[]){
    for (int i = last_id; i >= 0 ; i--)
        if (array[i]%2 != 0)
            return i;
}

long long sum_between_even_odd(int last_id, long long array[]){
    long long sum = 0;
    for (int i = index_first_even(last_id, array); i < index_last_odd(last_id, array); ++i)
        sum += llabs(array[i]);

    return sum;
}

long long sum_before_even_and_after_odd(int last_id, long long array[]){
    long long sum = 0;
    for (int i = 0; i < index_first_even(last_id, array); i++) 
        sum += llabs(array[i]);

    for (int i = index_last_odd(last_id, array); i <= last_id; i++)
        sum += llabs(array[i]);

    return sum;
}


int main(){
    int choice;
    scanf("%d", &choice);
    long long array[100];
    int last_id = 0;
    char symbol_after;

    while (scanf("%lld%c", &array[last_id], &symbol_after) && symbol_after != '\n')
        last_id++;

    switch (choice){
        case 0:
            printf("%d\n", index_first_even(last_id, array));
            break;
        case 1:
            printf("%d\n", index_last_odd(last_id, array));
            break;
        case 2:
            printf("%lld\n", sum_between_even_odd(last_id, array));
            break;
        case 3:
            printf("%lld\n", sum_before_even_and_after_odd(last_id, array));
            break;
        default:
            printf("Данные некорректны\n");
    }
    return 0;
}
