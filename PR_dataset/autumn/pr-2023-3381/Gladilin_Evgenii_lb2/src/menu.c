#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"

int main(){
        int arr[1000],i,k,x,a;
        scanf("%d", &x);

        do{
                scanf("%d", &arr[i]);
                i++;
        }while(getchar()!='\n');
        switch(x){
                case 0:
                        a = index_first_negative(arr,i);
                        if(a == -2){
                                printf("Данные некорректны\n");
                        }else{
                                printf("%d\n",a);}
                        break;
                case 1:
                        a = index_last_negative(arr,i);
                        if(a == -2){
                                printf("Данные некорректны\n");
                        }else{
                                printf("%d\n",a);}
                        break;
                case 2:
                        multi_between_negative(arr,i);
                        break;
                case 3:
                        multi_before_and_after_negative(arr,i);
                        break;
                default:
                        printf("Данные некорректны\n");
        }
        return 0;
}

