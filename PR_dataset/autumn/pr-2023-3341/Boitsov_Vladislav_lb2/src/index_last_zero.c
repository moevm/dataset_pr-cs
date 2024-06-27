int get_index_last_zero(int array_real_size, int array[])
{
	for(int i=array_real_size-1;i>=0;i--)
	{
		if(array[i]==0)
		{
			return i;
		}
	}
	
}