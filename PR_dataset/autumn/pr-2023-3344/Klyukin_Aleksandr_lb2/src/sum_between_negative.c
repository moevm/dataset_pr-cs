#include "sum_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
#include <stdlib.h>
int sum_between_negative(int lenght,int array[]){
	int cnt;
	int left = index_first_negative(lenght, array);
	int right = index_last_negative(lenght, array);
		for (left; left < right; left++){
			cnt += abs(array[left]);
		}
		return cnt;
}