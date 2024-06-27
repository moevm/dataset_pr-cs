#include <stdio.h>

#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"

int main() {
    int n;
    int array[100];
    int length = 0;

    scanf("%d", &n);
    int i;
    for (i = 0; i < 100; i++) {
        array[i] = 0;
    }
        
    while(getchar() != '\n' && length < 100) {
        scanf("%d", &array[length]);
        length++;
    }

    switch(n){
            case 0:
                printf("%d\n", index_first_even(array));
                break;
            case 1:
                printf("%d\n", index_last_odd(array));
                break;
            case 2:
                printf("%d\n", sum_between_even_odd(array));
                break;
            case 3:
                printf("%d\n", sum_before_even_and_after_odd(array));
                break;
            default:
                printf("Данные некорректны\n");
    }
    
    return 0;
}
