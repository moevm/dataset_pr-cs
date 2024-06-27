#include<stdio.h>
#include"index_first_negative.h"
#include"index_last_negative.h"
#include"multi_between_negative.h"
#include"multi_before_and_after_negative.h"



int main()
{
	int value; // значение
	int counter=0; // размер массива
    int arr_of_integers[20]; // массив целых чисел
	scanf("%d", &value);
	while(getchar()!='\n'){
		scanf("%d",&arr_of_integers[counter]);
		counter++;
	}
	switch (value){
		case 0:
			{
				printf("%d\n",index_first_negative(arr_of_integers,counter));
				break;
			}
		case 1:
			{
				printf("%d\n",index_last_negative(arr_of_integers,counter));
				break;
			}
		case 2:
			{
				printf("%d\n",multi_between_negative(arr_of_integers,counter));
				break;
			}
		case 3:
			{
				printf("%d\n",multi_befor_and_after_negative(arr_of_integers,counter));
				break;
			}
		default:
		        printf("Данные некорректны\n");
		       	break;
	}
   return 0;
}
