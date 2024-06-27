#include <stdio.h>
#include "max.h"
#include "min.h"

int diff(int n, int* arr) {
	return max(n, arr) - min(n, arr);
}
