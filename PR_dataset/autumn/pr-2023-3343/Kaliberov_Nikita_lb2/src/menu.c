#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"
const int n = 100;

int main(){
    int a;
    int b[100];
    int s = 0;
    char c;
    scanf("%d", &a);
    while(c != '\n'){
        scanf("%d%c", &b[s++],&c);
    }
    switch(a){
        case 0:
            printf("%d\n", index_first_negative(b, s));
            break;
        case 1:
            printf("%d\n", index_last_negative(b, s));
            break;
        case 2:
            printf("%d\n", sum_between_negative(b, s));
            break;
        case 3:
            printf("%d\n", sum_before_and_after_negative(b, s));
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }
}
