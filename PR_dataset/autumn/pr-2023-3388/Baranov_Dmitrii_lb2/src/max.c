#include<stdio.h>
#include"max.h"

int max(int masiv[], int s) { 
 
	int max1 = -9999999; 
 
	for (int i = 0; i < s; i++) {

		if (masiv[i] > max1) { 
 
			max1 = masiv[i]; 
 
        	} 
 
	} 
 
	return max1;}
