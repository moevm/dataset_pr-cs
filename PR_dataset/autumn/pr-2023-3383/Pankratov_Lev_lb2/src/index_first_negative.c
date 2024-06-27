#include <stdio.h>
#include "index_first_negative.h"

int index_first_negative(int masive[], int countElements) {
    
	for(int i = 0; i < countElements; i++) {
        	if (masive[i] < 0)
            		return i;
    	}
}
