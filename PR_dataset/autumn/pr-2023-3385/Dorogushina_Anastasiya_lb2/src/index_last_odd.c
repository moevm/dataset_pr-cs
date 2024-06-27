#include <stdlib.h>
#include "index_last_odd.h"
int index_last_odd(int arr[], int len){
	int r,i;
 	for(i = 0; i < len; i++){
        	if(abs(arr[i]) % 2 == 1){
            		r = i;
        	}
    	}
    	return r;
}
