int index_first_negative(int arr[], int length) 
{
	for (int i = 0; i < length; i++) {
		if (arr[i] < 0) {
			return i;
		}
	}
}
