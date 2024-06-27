#include <stdio.h>
#include <stdlib.h>
#include "index_last_odd.h"

int index_last_odd(int mas[], int len){
	for(int k = len-1;; k--) {
	    if ((abs(mas[k])%2) == 1){
	        return k;
	    }
    }
}
