#include <stdio.h>
int index_first_negative(int arr[],int size){
        int index_first_neg = -1;
        for(int i=0;i<size;i++){
                if (arr[i]<0){
                        index_first_neg = i;
                        break;
                }
        }
        if (index_first_neg != -1){
        return index_first_neg;}
        else{puts("Данные некорректны");}
}
