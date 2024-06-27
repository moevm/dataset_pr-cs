#include <stdio.h>
#include "multi_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_between_negative(int masive[], int a, int b) {
	int rez = 1;
    	for(int i = a; i < b; i++)
        	rez *= masive[i];

    	return rez;
}
