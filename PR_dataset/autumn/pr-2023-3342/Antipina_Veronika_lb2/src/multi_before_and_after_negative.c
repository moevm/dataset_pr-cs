#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"

void  multi_before_and_after_negative(int arr[],int size){
        int multi = 1;
	int index_first_neg, index_last_neg;

	index_first_neg = index_first_negative(arr,size);
	index_last_neg = index_last_negative(arr,size);

	for(int i=0;i<index_first_neg;i++){
		multi*=arr[i];
	}

	for(i=index_last_neg;i<size;i++){
		multi*=arr[i];
	}

        printf("%d\n", multi);
}
