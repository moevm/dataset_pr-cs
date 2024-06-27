#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 100

int index_first_even(int arr[],int length)
{
 for(int result=0;result<length;result++)
 {
  if(arr[result]%2==0)
  return result;
 }
}

int index_last_odd(int arr[], int length)
{
 int result;
 for(int i=0;i<length;i++)
 {
  if(abs(arr[i])%2==1)
  result = i;
 }
 return result;
}

int sum_between_even_odd(int arr[],int length)
{
 int result=0;
 int first_even = index_first_even(arr,length);
 int last_odd = index_last_odd(arr,length);
 for(int i=first_even;i<last_odd;i++)
 result+=abs(arr[i]);
 return result;
}
int sum_before_even_and_after_odd(int arr[], int length)
{
 int result=0;
 int first_even = index_first_even(arr,length);
 int last_odd = index_last_odd(arr,length);
 for(int i=0;i<first_even;i++)
 result+=abs(arr[i]);
 for(int i=last_odd;i<length;i++)
 result+=abs(arr[i]);
 return result;
}
int switch_menu(int value, int arr[], int length)
{
    switch(value)
 {
  case 0:
   printf("%d", index_first_even(arr,length));
   return 0;
  case 1:
   printf("%d", index_last_odd(arr,length));
   return 0;
  case 2:
   printf("%d", sum_between_even_odd(arr,length));
   return 0;
  case 3:
   printf("%d",sum_before_even_and_after_odd(arr,length));
   return 0;
  default:
      printf("Данные некорректны");
      return 0;
 }
}
int main()
{
 int value;
 scanf("%d",&value);
 int arr[MAX_LENGTH];
 int length=0;
 while(scanf("%d", &arr[length])==1)
 length++;
 switch_menu(value, arr, length);
}
