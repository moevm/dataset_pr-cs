#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"
#define N 100

int main(){
        int a,n,c,i=0;
        scanf("%d", &n);
        int s[N];
        while( ( c=getchar() ) != '\n' ){
                scanf("%d",&a);
                s[i] = a;
                i++;
        }
        switch(n){
                case 0:
                        printf("%d", index_first_negative(s,i));
                        break;
                case 1:
                        printf("%d", index_last_negative(s,i));
                        break;
                case 2:
                        printf("%d", sum_between_negative(s,i));
                        break;
                case 3:
                        printf("%d", sum_before_and_after_negative(s,i));
                        break;
                default:
                        printf("Данные некорректны");
        }
        printf("\n");
        return 0;
}
