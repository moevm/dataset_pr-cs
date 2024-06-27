#include "fill_array_and_get_len.h"
#include <stdio.h>
//заполнение массива и получение его длины
int fill_array_and_get_len(int array[]){
	int len = 0;
	do{
		scanf("%d",&array[len++]);
	}
        while (len<100 &&  getchar()!='\n');
	return len;

}
