#include "get_result.h"
void get_result(int number,int* arr,int size){
        switch(number){
            case 0:
            printf(OUTPUT,max(arr,size));
            break;
            case 1:
            printf(OUTPUT,min(arr,size));
            break;
            case 2:
           printf(OUTPUT,diff(arr,size));
            break;
            case 3:
            printf(OUTPUT,sum(arr,size));
            break;
            default:
            printf( "Данные некорректны");
            
        }
    
}
