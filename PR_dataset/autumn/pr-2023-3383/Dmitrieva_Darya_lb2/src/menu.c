#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"
int main(){
    int n;
    scanf("%d",&n);
    int array[20];
    int len = 0;
    while (len <= 20 && scanf("%d", &array[len]) == 1) {
        len++;
        if (getchar() == '\n') {
            break;
        }
    }
    switch(n){
            case 0:
                if (index_first_negative(array, len)!=-1){
                    printf("%d\n",index_first_negative(array, len));
                }
                else{
                    printf("Данные некорректны\n");
                }
                break;
            case 1:
                if (index_last_negative(array, len)!=-1){
                printf("%d\n",index_last_negative(array, len));
                }
                else{
                    printf("Данные некорректны\n");
                }
                break;
            case 2:
                printf("%d\n",multi_between_negative(array, len));
                break;
            case 3:
                printf("%d\n",multi_before_and_after_negative(array, len));
                break;
            default:
                printf("Данные некорректны\n");
                break;
    }
}