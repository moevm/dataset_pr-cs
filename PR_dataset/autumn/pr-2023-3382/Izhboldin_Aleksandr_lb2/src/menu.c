#include <stdio.h>
#include <stdlib.h>

#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"

#define INDEX_FIRST_EVEN 0
#define INDEX_LAST_ODD 1
#define SUM_BETWEEN_EVEN_ODD 2
#define SUM_BEFORE_EVEN_AND_AFTER_ODD 3

int main(){
    int choice;
    scanf("%d", &choice);
    long long array[100];
    int last_id = 0;
    char symbol_after;

    while (scanf("%lld%c", &array[last_id], &symbol_after) && symbol_after != '\n')
        last_id++;

    switch (choice){
        case INDEX_FIRST_EVEN:
            printf("%d\n", index_first_even(last_id, array));
            break;
        case INDEX_LAST_ODD:
            printf("%d\n", index_last_odd(last_id, array));
            break;
        case SUM_BETWEEN_EVEN_ODD:
            printf("%lld\n", sum_between_even_odd(last_id, array));
            break;
        case SUM_BEFORE_EVEN_AND_AFTER_ODD:
            printf("%lld\n", sum_before_even_and_after_odd(last_id, array));
            break;
        default:
            printf("Данные некорректны\n");
    }
    return 0;
}
