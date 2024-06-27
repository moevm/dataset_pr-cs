#include <stdio.h>

int index_last_negative(int arr[], int size){
        int index_last_neg;

        for(int i=0;i<size;i++){
                if (arr[i]<0){
                        index_last_neg = i;
                }
        }
	return index_last_neg;
}
