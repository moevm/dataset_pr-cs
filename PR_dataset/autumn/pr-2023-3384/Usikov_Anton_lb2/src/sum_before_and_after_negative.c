#include <stdio.h>
#include<stdlib.h>
#include"index_first_negative.h"
#include"index_last_negative.h"

int sum_before_and_after_negative(int a[], int a_length)
{
  int sum = 0;
 for(int i = 0; i<a_length; i++) 
 if (i < index_first_negative(a, a_length) || i >= index_last_negative(a, a_length))
 sum += abs(a[i]);
 return sum;
}