#include <stdio.h>
#include <stdlib.h>


//..............................
int zero(int arr[], int n)
{
int index_first_even = 0;
    for (int i=0;i<n;i++)
    	{
    	   if (abs(arr[i]) % 2 == 0)
    		{
    			int index_first_even = i;
       			return index_first_even;
    		}
    	}

}
//.............................
int one(int a[], int n)
{
int index_last_odd = 0;
	for (int i = n - 1;i >= 0; i--)
	{
		if (abs(a[i]) % 2 != 0)
		{
			index_last_odd = i;
			return index_last_odd;
		}
	}
}
//...................................
int two(int a[], int n)
{
  int sum_between_even_odd = 0;
  int first = zero(a,n);
  int last = one(a,n);
  for (int i=first;i<last;i++)
  {
  	sum_between_even_odd += abs(a[i]);

  }
    return sum_between_even_odd;
}
//..................................

int three(int a[], int n)
{
  int sum_before_even_and_after_odd = 0;
  int first = zero(a,n);
  int last = one(a,n);
  for (int i = 0;i<first;i++)
  {
  	sum_before_even_and_after_odd += abs(a[i]); 
  }
  for (int i = last; i < n;i++)
  {
	sum_before_even_and_after_odd += abs(a[i]);  
  
  }
  return sum_before_even_and_after_odd;
}
//........................................


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
    		printf("%d\n", zero(a,count));
    		break;
    	case 1:
    		printf("%d\n", one(a,count));
    		break;
    	case 2:
    		printf("%d\n", two(a,count));
    		break;
    	case 3:
    		printf("%d\n", three(a,count));
    		break;
    	default:
    		printf("Данные некорректны");
    		break;
    	}
 
 return 0;
}








