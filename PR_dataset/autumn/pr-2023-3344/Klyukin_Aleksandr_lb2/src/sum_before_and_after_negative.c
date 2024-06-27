#include "sum_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
#include <stdlib.h>
int sum_before_and_after_negative(int lenght, int array[]){
	int i = 0;
	int cnt;
	int left = index_first_negative(lenght, array);
	int right = index_last_negative(lenght, array);
	for (i; i<lenght; i++){
		if ((i < left) || (i >= right)){
			cnt += abs(array[i]);
		}
		else{
			continue;
		}
	}
	return cnt;
}