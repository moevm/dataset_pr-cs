int index_last_negative(int a[], int count)
{
    int last;
    for(int i=0; i<count; i++)
    {
        if (a[i]<0)
        {
            last=i;
        }
    }
    return last;
}