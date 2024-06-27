#include<stdio.h>
#include"sum.h"

int sum(int introValues[], int len) {
       int index; 
       int minNum = 9999999;
       int summ = 0; 
       for(int i = (len-1); i >= 0; i--) {
              if (introValues[i] <= minNum) {
                     minNum = introValues[i];
                     index = i;
        	} 
 
	} 
 
	for (int j = 0; j <index; j++) {
              summ = summ + (introValues[j]);
	}
       return summ;
}	
