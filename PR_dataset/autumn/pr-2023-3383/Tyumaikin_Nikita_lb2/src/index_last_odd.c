int index_last_odd(int *arr, int len){
	for(int i=len - 1;i >= 0;--i){
		if (arr[i] % 2 != 0)
			return i;
	}
}
