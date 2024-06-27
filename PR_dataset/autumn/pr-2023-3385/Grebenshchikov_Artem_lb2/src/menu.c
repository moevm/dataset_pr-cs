#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"

int main(){
        int c, i = 0, n;
        scanf("%d", &n);
        int m[100];
        do{
        scanf("%d", &m[i]);
        ++i;
        } while(( c =getchar())!= '\n');
        switch(n){
                case 0:
                        printf("%d\n", index_first_zero(m, i));
                        break;
                case 1:
                        printf("%d\n", index_last_zero(m, i));
                        break;
                case 2:
                        printf("%d\n", sum_between(m, i));
                        break;
                case 3:
                        printf("%d\n", sum_before_and_after(m, i));
                        break;
                default:
                        printf("Данные некорректны\n");
        }
        return 0;
}
