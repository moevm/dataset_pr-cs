int max(int arr[], int arr_size)
{
    int mx = arr[0];
    for (int i = 1; i < arr_size; ++i)
    {
        if (arr[i] > mx)
        {
            mx = arr[i];
        }
    }
    return mx;
}