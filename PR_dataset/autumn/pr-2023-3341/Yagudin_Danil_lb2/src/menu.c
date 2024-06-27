#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"

#define INPUT_SIZE 2000
#define OUT "%d\n"

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
         printf(OUT,index_first_negative(array, array_size));
         break;
      case '1':
         printf(OUT,index_last_negative(array, array_size));
         break;
      case '2':
         printf(OUT,multi_between_negative(array, array_size));
         break;
      case '3':
         printf(OUT,multi_before_and_after_negative(array, array_size));
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
