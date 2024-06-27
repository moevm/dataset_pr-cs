#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"

int main(){
        int arr[100];
        int i = 0;
        int l;
        int cmd;
        scanf("%d", &cmd);
        char slashN;
        do{
                scanf("%d%c", &arr[i], &slashN);
                i++;
        }
        while(slashN != '\n' && i < 101);
                l = i;
                if(index_last_zero(arr,l) != -1)
                        switch(cmd){
                                case 0:
                                        {printf("%d\n", index_first_zero(arr,l));
                                        break;}
                                case 1:
                                        {printf("%d\n", index_last_zero(arr,l));
                                        break;}
                                case 2:
                                        {printf("%d\n", sum_between(arr,l));
                                        break;}
                                case 3:
                                        {printf("%d\n", sum_before_and_after(arr,l));
                                        break;}
                                default:
                                        printf("Данные некорректны\n");
                        }
                else
                        printf("Данные некорректны");
}
