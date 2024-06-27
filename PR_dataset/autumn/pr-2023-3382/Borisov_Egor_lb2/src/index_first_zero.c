int index_first_zero(int massive[], int i, int len)
{
    int zero_f = 0;
    for(i = 0; i < len; i++)
    {
        if((massive[i]) == 0)
        {
            zero_f = i;
            return zero_f;
            break;
        }
    }
}
