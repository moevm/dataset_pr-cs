#include <stdio.h> 
#include <stdlib.h> 
#include "index_last_negative.h"
#include "index_first_negative.h"
#include "sum_before_and_after_negative"
#include "sum_between_negative"
void Solution(int a, int Mas[100], int len){
    int ans;
    switch(a){
        case 0:
            ans = index_first_negative(Mas);
            if(ans!=-1){
                printf("%d\n", ans);
            }
            else{
                printf("Данные некорректны");
            }
            break;
        case 1:
            ans = index_last_negative(Mas, len);
            if(ans!=-1){
                printf("%d\n", ans);
            }
            else{
                printf("Данные некорректны");
            }
            break;
        case 2:
            ans = sum_between_negative(Mas, len);
            if(ans!=-1){
                printf("%d\n", ans);
            }
            else{
                printf("Данные некорректны");
            }
            break;
        case 3:
            ans = sum_before_and_after_negative(Mas, len);
            if(ans!=-1){
                printf("%d\n", ans);
            }
            else{
                printf("Данные некорректны");
            }
            break;
        default:
            printf("Данные некорректны");
    
    }
}
