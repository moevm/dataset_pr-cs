#include <stdio.h>
#include "multi_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_before_and_after_negative(int masive[], int a, int b, int countElements) {
 	int rez = 1;
    	for(int i = 0; i < a; i++)
        	rez *= masive[i];
    	for(int i = b; i < countElements; i++)
        	rez *= masive[i];

    	return rez;
}
