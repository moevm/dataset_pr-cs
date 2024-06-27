int min(int arr[], int arr_size)
{
    int mn = arr[0];
    for (int i = 1; i < arr_size; ++i)
    {
        if (arr[i] < mn)
        {
            mn = arr[i];
        }
    }
    return mn;
}