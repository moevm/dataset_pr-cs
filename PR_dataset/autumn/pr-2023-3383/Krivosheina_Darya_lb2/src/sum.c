#include <stdio.h>
#include "sum.h"
#include "min.h"

int sum(int massif4[], int len4){
	int minim = min(massif4, len4);
	int summa = 0;
	for (int i = 0; i < len4; i++){
		if (massif4[i] == minim){
			break;
		} 
		summa += massif4[i];
	}
	return summa;
}
