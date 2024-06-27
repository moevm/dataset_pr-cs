#include<stdio.h>
#include"sum.h"

int sum(int masiv[], int s) { 
 
	int index; 
 
	int min2 = 9999999; 
 
	int summ = 0; 
 
	for(int i = (s-1); i >= 0; i--) { 
 
        	if (masiv[i] <= min2) { 
 
        		min2 = masiv[i]; 
 
        		index = i; 
 
        		} 
 
		} 
 
	for (int j = 0; j <index; j++) { 
 
        	summ = summ + (masiv[j]); 
 
		} 
	
       return summ ;}	
