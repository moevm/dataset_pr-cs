#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define INPUT_SIZE 2000

int index_first_negative( int array[], int array_size)
{
   for (int i = 0; i < array_size; i ++)
   {
      if (array[i] < 0)
      {
         return i;
      }
   }
   return 0;
}

int index_last_negative(int array[], int array_size)
{
   for (int i = array_size; i > 0; i --)
   {
      if (array[i] < 0)
      {
         return i;
      }
   }
   return 0;
}

int multi_between_negative(int array[], int array_size)
{
   int multi_result = 1;
   int start = index_first_negative(array, array_size);
   int end = index_last_negative(array, array_size);
   for (int i = start; i < end; i ++)
   {
      multi_result *= array[i];
   }
   if (multi_result == 1)
   {
      return 0;
   } 
   else
   {
   return multi_result;   
   }
}

int multi_before_and_after_negative(int array[], int array_size)
{
   int multi_result = 1;
   int start = index_last_negative(array, array_size);
   int end = index_first_negative(array,array_size);
   for (int i = 0; i < end; i ++)
   {
      multi_result *= array[i];
   }
   for (int i = start; i < array_size; i ++)
   {
      multi_result *= array[i];
   }
   if (multi_result == 1) 
   {
      return 0;
   }
   else
   {
      return multi_result;
   }
}

void create_array(char input[], int array[], int *size) {
    char *xstr;
    xstr = strtok(input, " ");
    xstr = strtok(NULL, " ");

    while (xstr != NULL) {
        array[(*size)++] = atoi(xstr);
        xstr = strtok(NULL, " ");
    }
}

void make_command(char command, int array[], int array_size)
{
   switch(command) {
      case '0':
         printf("%d\n",index_first_negative(array, array_size));
         break;
      case '1':
         printf("%d\n",index_last_negative(array, array_size));
         break;
      case '2':
         printf("%d\n",multi_between_negative(array, array_size));
         break;
      case '3':
         printf("%d\n",multi_before_and_after_negative(array, array_size));
         break;
      default:
         printf("Данные некорректны\n");
   }
}

int main() {
   char input[INPUT_SIZE];
   fgets(input, INPUT_SIZE, stdin);

   char command = input[0];

   int using_array[20];
   int using_array_size = 0;

   create_array(input, using_array, &using_array_size);
   make_command(command, using_array, using_array_size);
   return 0;
}
