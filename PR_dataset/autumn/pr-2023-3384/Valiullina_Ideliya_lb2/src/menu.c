#include <stdio.h>
#include <stdlib.h>

#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"

#define N 100

int main()
{
    int f, n = 0;
    scanf("%d", &f);

    int a[N];
    char x = getchar();
    for(int i = 0; i < N; i++){
        if(x == '\n')
            break;
        else{
            scanf("%d", &a[i]);
            x = getchar();
            n++;
        }
    }

    switch(f){
        case 0:
            printf("%d\n", abs_max(a, n));
            break;
        case 1:
            printf("%d\n", abs_min(a, n));
            break;
        case 2:
            printf("%d\n", diff(a, n));
            break;
        case 3:
            printf("%d\n", sum(a, n));
            break;
        default:
            printf("Данные некорректны\n");
    }
    return 0;
}
