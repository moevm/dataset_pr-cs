#include<stdio.h>
#include"min.h"

int min(int introValues[], int len) { 
	int minNum = 9999999; 
	for (int i = 0; i < len; i++) { 
        	if (introValues[i] < minNum) { 
        		minNum = introValues[i]; 
			} 
		}
	return minNum;
}