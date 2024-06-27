#include <stdio.h>
#define N 21
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"
int main(){
    char s;
    int mas[N];
    int nz;
    int count;
    scanf("%d", &nz);
    for(int i = 0; i < N; i++){
        scanf("%d%c", &mas[i], &s);
        if(i == N || s == '\n'){
            count = i + 1;
            break;
            
        }
    }
    switch(nz){
        case(0):
            printf("%d\n", index_first_negative(mas, count));
            break;
        case(1):
            printf("%d\n", index_last_negative(mas, count));
            break;
        case(2):
            printf("%d\n", multi_between_negative(mas, count));
            break;
        case(3):
            printf("%d\n", multi_before_and_after_negative(mas, count));
            break;
        default:
            printf("Данные некорректны\n");
    }
    return 0;
}

