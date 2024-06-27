int index_last_negative(int arr[], int len)
{
    int return_value = 0;
    for (int i = 0; i < len; i++)
    {
        if (arr[i] < 0)
        {
            return_value = i;
        }
    }
    return return_value;
}