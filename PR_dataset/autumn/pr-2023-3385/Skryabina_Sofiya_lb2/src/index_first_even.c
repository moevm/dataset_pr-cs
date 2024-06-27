#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"

int index_first_even(int mas[], int len){
	for(int k = 0;; k++){
	    if ((abs(mas[k])%2) == 0){
	        return k;
	    }
    }
}
