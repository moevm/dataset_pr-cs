int max(int *array, int sizeOfArray) {
	int maximum = 0;
	for (int i = 0; i < sizeOfArray; ++i) {
		if (array[i] > maximum)
			maximum = array[i];
	}
	return maximum;
}
