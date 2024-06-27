#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"
int main(){
    char space;
    int length;
    int nomer;
    scanf("%d",&nomer);
    int list[20];
    for(int i = 0;i<21;i++){
        scanf("%d%c",&list[i],&space);
        if(i == 20||space == '\n'){
            length = i+1;
            break;
        }
        }
    switch(nomer){
        case(0):
            printf("%d \n",index_first_negative(list,length));
            break;
        case(1):
            printf("%d \n",index_last_negative(list,length));
            break;
        case(2):
            printf("%d \n",multi_between_negative(list,length));
            break;
        case(3):
            printf("%d \n",multi_before_and_after_negative(list,length));
            break;
        default:
            printf("Данные некорректны\n");
        
    }
}
