#include <stdio.h>
#include "arr_input.h"
int arr_input(int arr_len, int* A){
	int num;
	while (1) { 
       	  if (scanf("%d", &num) == 1) { 
       	  }
	  else {
        	break; 
       	  }
	  A[arr_len] = num;
      	  arr_len += 1;
    	}
    return arr_len;
}
