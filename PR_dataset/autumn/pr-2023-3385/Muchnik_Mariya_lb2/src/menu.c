#include <stdio.h>

#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"

int main()
{
	int n, arr[100], len = 0;
    char c;
    
    scanf("%d", &n);
    
    do {
        scanf("%d", &arr[len]);
        len++;
    } while(c = getchar() != '\n');
    
    switch(n){
        case 0:
            printf("%d\n", index_first_zero(arr, len));
            break;
        case 1:
            printf("%d\n", index_last_zero(arr, len));
            break;
        case 2:
            printf("%d\n", sum_between(arr, len));
            break;
        case 3:
            printf("%d\n", sum_before_and_after(arr, len));
            break;
        default:
            printf("Данные некорректны\n");
    }
}
