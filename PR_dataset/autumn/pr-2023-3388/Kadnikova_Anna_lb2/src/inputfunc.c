#include <stdio.h>
#include <stdlib.h>
#include "inputfunc.h"
#define N 100

int inputfunc(){
	int chisla[N] = {0};
	int len = 0;
    	int i = 0;
	do {
        	scanf("%d", &chisla[i]);
        	i++;
        	len++;
    	}
    	while (getchar() != '\n');
	return chisla;

}