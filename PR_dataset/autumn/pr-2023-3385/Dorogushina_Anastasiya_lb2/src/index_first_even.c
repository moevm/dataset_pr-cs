#include <stdlib.h>
#include "index_first_even.h"
int index_first_even(int arr[], int len){
	int i;
   	for(i = 0; i < len; i++){
		if(abs(arr[i]) % 2 == 0){
			return i;
            		break;
        	}
    	}
}
