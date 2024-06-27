int sum(int arr[], int size)
{
    int min_index = 0;

    for (int i = 1; i < size; i++)
    {
        if (arr[i] < arr[min_index])
        {
            min_index = i;
        }
    }

    int sum = 0;
    for (int i = 0; i < min_index; i++)
    {
        sum += arr[i];
    }

    return sum;
}