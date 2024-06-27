#include <stdio.h>
#include<stdlib.h> 

int index_first_negative(int a[], int a_length)
{
    int index;
 for(int i=0;i<a_length;i++) 
 {
     if (a[i] < 0)
  {index = i;
      break;}
 }
 return index;
}

int index_last_negative(int a[], int a_length)
{
  int index;
 for(int i=a_length-1;i>=0;i--) 
 {
     if (a[i] < 0)
  {index = i;
      break;}
 }
 return index;
}

int sum_between_negative(int a[], int a_length)
{
   int sum = 0;
 for(int i = index_first_negative(a, a_length); i < index_last_negative(a, a_length); i++) 
 sum += abs(a[i]);
 return sum;
}

int sum_before_and_after_negative(int a[], int a_length)
{
  int sum = 0;
 for(int i = 0; i<a_length; i++) 
 if (i < index_first_negative(a, a_length) || i >= index_last_negative(a, a_length))
 sum += abs(a[i]);
 return sum;
}



int main()
{
    int array[100];
    char enter;  
    int input;
    int array_length = 0;
    scanf("%d", &input);
    for(int i=0; i<100; i++)
    {
        scanf("%d%c", &array[i], &enter);
        array_length++;
        if (enter == '\n') 
        break;  
    }
    switch(input)
    {
                case 0:
        printf("%d\n", index_first_negative(array, array_length));
        break;
        
        case 1:
        printf("%d\n", index_last_negative(array, array_length));
        break;
        
        case 2:
        printf("%d\n", sum_between_negative(array, array_length));
        break;
        
        case 3:
        printf("%d\n", sum_before_and_after_negative(array, array_length));
        break;
        default:
        printf("Данные некорректны\n");
        break;
    }
 return 0;
}