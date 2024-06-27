#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"

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
