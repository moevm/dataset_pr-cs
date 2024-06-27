#include <stdio.h>
#include "DataReading.h"

#define LEN_ARRAY_OF_NUMBER 100
#define LEN_FUNCTION_ANSWER_ARRAY 102
int* dataReading(){
	int array[LEN_ARRAY_OF_NUMBER];
	static int functionAnswerArray[LEN_FUNCTION_ANSWER_ARRAY];
	int i = 0, lenghtArray = 0, functionNumber = -1;
	do {
		       	scanf("%d", &array[i]);
			lenghtArray++;
			i++;

	} while(getchar() != '\n');
	
	functionAnswerArray[0] = lenghtArray-1;
	for (i = 1; i <= lenghtArray; i++)
		functionAnswerArray[i] = array[i-1];
	return functionAnswerArray;
}
