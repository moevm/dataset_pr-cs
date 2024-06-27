int index_last_zero(int arr[], int CNT_ARR){
	int ind_last = 0;
	for (int i = CNT_ARR-1; i >= 0; i--){
		if (arr[i] == 0) {
			ind_last = i;
			return ind_last;
		}
	}
	return ind_last;
}