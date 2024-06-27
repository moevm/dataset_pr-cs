int get_min(int arr[], int arr_len)
{
	int min = arr[0];

	for (int i = 0; i <= arr_len; i++)
	{
		if (arr[i] < min){
			min = arr[i];
		}
	}
	return min;
}