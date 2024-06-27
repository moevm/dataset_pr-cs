#include <stdio.h>
#include<stdlib.h> 

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