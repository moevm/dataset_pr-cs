#include<stdio.h>

int counter=0; // размер массива

int index_first_negative(int *arr_of_integers)
{
	int f_index=-1; // индекс первого отрицательного элемента
	for(int i=0;i<counter;i++)
	{
        if(arr_of_integers[i]<0)
	     {
		    f_index=i;
		    break;
	     }
	}
	return f_index;
}

int index_last_negative(int *arr_of_integers)
{
	int l_index=-1; // индекс последнего отрицательного элемента
	for(int i=counter-1;i>-1;i--)
	{
		if(arr_of_integers[i]<0)
		{
			l_index=i;
			break;
		}
	}
	return l_index;
}

int multi_between_negative(int *arr_of_integers)
{
	int f1_index=index_first_negative(arr_of_integers); // индекс первого отрицательного э-та массива
	int l1_index=index_last_negative(arr_of_integers); // инидекс последнего отрицательного э-та массива
	int composition=1; // произведение искомых э-тов массива
	for(int i=f1_index;i<l1_index;i++)
	{
		composition*=arr_of_integers[i];
	}
	return composition;
}

int multi_befor_and_after_negative(int *arr_of_integers)
{
	int f2_index=index_first_negative(arr_of_integers); // индекс первого отрицательного э-та массива
	int l2_index=index_last_negative(arr_of_integers); // индекс последнего отрицательного э-та массива
	int composition2=1;
	for(int i=0;i<f2_index;i++)
	{
		composition2*=arr_of_integers[i];
	}
	for(int i=l2_index;i<counter;i++)
	{
		composition2*=arr_of_integers[i];
	}
	return composition2;
}

int main()
{
	int value; // значение
    int arr_of_integers[20]; // массив целых чисел
	scanf("%d", &value);
	while(getchar()!='\n'){
		scanf("%d",&arr_of_integers[counter]);
		counter++;
	}
	switch (value){
		case 0:
			{
				printf("%d\n",index_first_negative(arr_of_integers));
				break;
			}
		case 1:
			{
				printf("%d\n",index_last_negative(arr_of_integers));
				break;
			}
		case 2:
			{
				printf("%d\n",multi_between_negative(arr_of_integers));
				break;
			}
		case 3:
			{
				printf("%d\n",multi_befor_and_after_negative(arr_of_integers));
				break;
			}
		default:
		        printf("Данные некорректны\n");
		       	break;
	}
   return 0;
}

