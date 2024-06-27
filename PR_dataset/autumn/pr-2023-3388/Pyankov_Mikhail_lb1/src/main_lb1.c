#include <stdio.h>
#define MAX_INPUT_SIZE 20

void input_array_data(int *array, int *length)
{
    while(scanf("%d", array)==1)
    {
        *length+=1;
        array++;
    }
}

void input_key_data(int *key)
{
	scanf("%d", key);
}

int index_first_negative(int *array, int length)
{
	for(int i = 0; i < length; i++)
	{
		if(array[i] < 0)
		return i;
	}
    return -1;
}

int index_last_negative(int *array, int length)
{
	int ans = -1;
	for(int i = 0; i<length; i++)
	{
		if(array[i] < 0)
		ans = i;
	}
	return ans;
}

int input_data_checking(int array[], int key, int length)
{
    if(index_first_negative(array, length)==-1||(index_first_negative(array, length)==index_last_negative(array, length)&&key>1))
    {
        printf("Данные некорректны");
        return 0;
    }
    return 1;
}

int multi_between_negative(int *array, int length)
{
	int multi_between_negative_result = 1;
	for(int i = index_first_negative(array, length); i < index_last_negative(array, length); i++)
	multi_between_negative_result *= array[i];
	return multi_between_negative_result;
}

int multi_before_and_after_negative(int *array, int length)
{
	int multi_before_and_after_negative_result = 1;
	for(int i = 0; i < index_first_negative(array, length); i++)
	multi_before_and_after_negative_result *= array[i];
	for(int i = index_last_negative(array, length); i < length; i++)
	multi_before_and_after_negative_result *= array[i];
	return multi_before_and_after_negative_result;
}

void switch_function(int key, int *array, int length)
{
    switch(key)
	{
		case 0:
            printf("%d", index_first_negative(array, length));
			break;
		case 1:
            printf("%d", index_last_negative(array, length));
            break;
		case 2:
			printf("%d", multi_between_negative(array, length));
			break;
		case 3:
            printf("%d", multi_before_and_after_negative(array, length));
			break;
		default:
		    printf("Данные некорректны");
		    break;
	}
}

int main()
{
    int key;
	input_key_data(&key);
	int length = 0;
    int array[MAX_INPUT_SIZE];
    input_array_data(array, &length);
    if(input_data_checking(array, key, length))
    switch_function(key, array, length);
	return 0;
}
