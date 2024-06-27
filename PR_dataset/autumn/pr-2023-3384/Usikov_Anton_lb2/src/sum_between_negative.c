#include <stdio.h>
#include<stdlib.h>
#include"index_first_negative.h"
#include"index_last_negative.h"

int sum_between_negative(int a[], int a_length)
{
   int sum = 0;
 for(int i = index_first_negative(a, a_length); i < index_last_negative(a, a_length); i++) 
 sum += abs(a[i]);
 return sum;
}