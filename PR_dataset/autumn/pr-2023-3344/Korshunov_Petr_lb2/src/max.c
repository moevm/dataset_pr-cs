int get_max(int arr[], int arr_len)
{
	int max = arr[0];
	for (int i = 0; i <= arr_len; i++)
	{
		if (arr[i] > max){
			max = arr[i];
		}
	}
	return max;
}