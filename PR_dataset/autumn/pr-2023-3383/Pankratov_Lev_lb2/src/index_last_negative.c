#include <stdio.h>
#include "index_last_negative.h"

int index_last_negative(int masive[], int countElements) {
    
 	for(int i = countElements-1; i >= 0; i--) {
        	if (masive[i] < 0)
            	return i;
    	}
    
}
