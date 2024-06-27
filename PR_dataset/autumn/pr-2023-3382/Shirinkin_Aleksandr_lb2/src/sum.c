#include "abs_max.h"
int sum(int q[], int len_q) {
	int sum_m = 0, i = (abs_max(q, len_q));
	for (i;i < len_q; i++) {
		sum_m += q[i];
	}
	return sum_m;  
}
