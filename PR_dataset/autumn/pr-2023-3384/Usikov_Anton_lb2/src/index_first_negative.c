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