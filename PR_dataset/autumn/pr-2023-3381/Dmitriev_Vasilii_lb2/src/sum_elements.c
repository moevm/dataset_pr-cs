#include "sum_elements.h"
#include <stdlib.h>

int sum_elements(int array[], int start, int end){
     int sum_abs = 0;
	 if (start!=-1){
        	 for(int i=start;i<end;i++){
         		sum_abs+=abs(array[i]);

         	}
	 }
        return sum_abs;

}
