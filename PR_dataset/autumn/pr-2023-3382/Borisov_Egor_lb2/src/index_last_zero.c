int index_last_zero(int massive[], int i, int len)
{
    int zero_l = 0;
    for(i = 0; i < len; i++)
    {
        if((massive[i]) == 0)
        {
            zero_l = i;

        }
    }
    return zero_l;
}

