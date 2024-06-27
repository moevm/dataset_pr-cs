#include <stdio.h>		
#include "choose_option.h"
#include "max.h"
#include "min.h"
#include "sum.h"
#include "diff.h"
#include "arr_input.h"

int main(){
	int A[100] = {};
	int arr_len = 0;
	int option = choose_option();
	arr_len = arr_input(arr_len, A);
        switch(option){
         case 0: printf("%d\n", max(A, arr_len)); break;
         case 1: printf("%d\n", min(A, arr_len)); break;
         case 2: printf("%d\n", diff(A, arr_len)); break;
         case 3: printf("%d\n", sum(A, arr_len)); break;
         default: printf("Данные некорректны"); return 0;
        }

        }
 
