#include "diff.h"
#include "max.h"
#include "min.h"

int diff(int arr[], int n){
	return max(arr, n) - min(arr, n);
}
