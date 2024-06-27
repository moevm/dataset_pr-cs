#include "DataReading.h"
#include "choiseAnswer.h"
#define THE_INDEX_FROM_WHICH_THE_NUMBERS_TO_BE_PROCESSED_START 2
int main(){
	int *inputData;
	inputData = dataReading();
	int lenghtArray = inputData[0];
	int functionNumber = inputData[1];
	int array[lenghtArray];
	for (int i=THE_INDEX_FROM_WHICH_THE_NUMBERS_TO_BE_PROCESSED_START; i<lenghtArray+2;i++)
		array[i-2] = inputData[i];
	choiceAnswer(array, lenghtArray, functionNumber);
	return 0;	
}
