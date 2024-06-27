

int get_index_first_zero(int array_real_size, int array[])
{
	for(int i=0;i<array_real_size;i++)
	{
		if(array[i]==0)
		{
			return i;
		}
	}
}