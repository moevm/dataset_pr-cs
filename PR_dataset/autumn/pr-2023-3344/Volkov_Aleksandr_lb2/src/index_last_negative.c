int index_last_negative(int numbers[], int size){
	int index;
	for(int i = 0; i < size; i++){
		if(numbers[i] < 0){
			index = i;
		}
	}
	return index;
}