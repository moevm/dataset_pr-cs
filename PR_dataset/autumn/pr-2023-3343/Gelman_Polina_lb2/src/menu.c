#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"

int main()
{
    int num;
    scanf("%d",&num);    
    //заполняем массив
    
    int a[100];
    int count = 0;
    while (getchar() != '\n')
    	{
    		scanf("%d",&a[count]);
    		count++;
    		
    	}
    	
    	//условия
    	
    	switch(num){
    	case 0:
    		printf("%d\n", index_first_even(a,count));
    		break;
    	case 1:
    		printf("%d\n", index_last_odd(a,count));
    		break;
    	case 2:
    		printf("%d\n", sum_between_even_odd(a,count));
    		break;
    	case 3:
    		printf("%d\n", sum_before_even_and_after_odd(a,count));
    		break;
    	default:
    		printf("Данные некорректны");
    		break;
    	}
 
 return 0;
}
