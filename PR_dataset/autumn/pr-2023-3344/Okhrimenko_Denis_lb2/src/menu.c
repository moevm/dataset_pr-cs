#include <stdio.h>
#include "abs_min.h"
#include "abs_max.h"
#include "diff.h"
#include "sum.h"

#define MAX_SIZE_OF_ARRAY 100

int main()
{
    int ans;
    int count = 0;
    int arr[MAX_SIZE_OF_ARRAY];
    int check;
    scanf("%d", &check);

    while(getchar() != '\n'){
        scanf("%d", &arr[count++]);
    }

    switch (check){
        case 0:
            ans = abs_max(arr, count);
            printf("%d\n", ans);
            break;
        case 1:
            ans = abs_min(arr, count);
            printf("%d\n", ans);
            break;
        case 2:
            ans = diff(arr, count);
            printf("%d\n", ans);
            break;
        case 3:
            ans = sum(arr, count);
            printf("%d\n", ans);
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }
    return 0;
}

