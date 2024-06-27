#include <stdio.h>
#include "diff.h"
#include "max.h"
#include "min.h"
#include "sum.h"

int main()
{
    int value, arr[100], len = 0;
    scanf("%d", &value);
    
    for (int i = 0; i < 100; i++) {
        if (getchar() != '\n') {
            scanf("%d", &arr[i]);
            len++;
        }
        else break;
    }
    
    switch(value) {
        case 0:
            printf("%d\n", getMax(arr, len));
            break;
        case 1:
            printf("%d\n", getMin(arr, len));
            break;
        case 2:
            printf("%d\n", getDiff(arr, len));
            break;
        case 3:
            printf("%d\n", getSum(arr, len));
            break;
        default:
            printf("Данные некорректны");
        
    }

    return 0;
}