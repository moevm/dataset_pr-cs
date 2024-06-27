int index_last_odd(int arr[], int ans, int i)
{
    for (i = 0; i < 100; i++)
    {
        if(arr[i]%2!=0)
        {
            ans=i;
        }
    }
    return ans;
}
