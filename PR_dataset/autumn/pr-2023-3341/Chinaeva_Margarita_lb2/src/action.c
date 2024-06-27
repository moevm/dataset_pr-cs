#include <stdio.h>  
#include <stdlib.h>  
  
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"

int action(char value, int* array) { 
 switch (value) { 
 case '0': 
  printf(D, index_first_even(array)); 
  break; 
 case '1': 
  printf(D, index_last_odd(array)); 
  break; 
 case '2': 
  printf(D, sum_between_even_odd(array)); 
  break; 
 case '3': 
  printf(D, sum_before_even_and_after_odd(array)); 
  break; 
 default: 
  printf("Данные некорректны\n"); 
  break; 
 } 
 return 0; 
} 
