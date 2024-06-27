#include "abs_max.h"
#include "abs_min.h"
int diff(int q[], int len_q) {
	return (q[abs_max(q, len_q)] - q[abs_min(q ,len_q)]);
}
