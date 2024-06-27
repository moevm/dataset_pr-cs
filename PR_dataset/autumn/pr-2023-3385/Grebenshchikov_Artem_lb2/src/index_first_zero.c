#include "index_first_zero.h"

int index_first_zero(int mas[], int len){
	int g =0;
	for(; g < len; ++g){
		if (mas[g] == 0){
			return g;
		}
	}
}
