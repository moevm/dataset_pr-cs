int index_first_negative(int a[], int count)
{
    for(int i=0; i<count;i++)
    {
        if (a[i]<0)
        {
            return i;
        }
    }
    return -1;
}