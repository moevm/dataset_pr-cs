#include <stdio.h>

#include "min.h"
#include "max.h"
#include "diff.h"

int diff(int* arr, int len){
    
	return max(arr, len) - min(arr, len);
}
