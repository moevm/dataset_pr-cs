int index_last_negative (int arr[], int length)
{
	for (int i = length - 1; i >= 0; i--) {
		if (arr[i] < 0) {
			return i;
		}
	}
}
