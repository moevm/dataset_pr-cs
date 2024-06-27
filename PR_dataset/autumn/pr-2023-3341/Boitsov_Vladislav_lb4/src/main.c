#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define NUM_OF_ELEMENTS 1000

void print(int* array);
int comparator(const void* firstElem, const void* secondElem)
{
	int firstNum=*((int*)firstElem), secondNum=*((int*)secondElem);
	if(firstNum<secondNum)
		return -1;
	else if (firstNum>secondNum)
		return 1;
	return 0;
}

clock_t getBubbleSortTime(int* arr)
{
	int sortedArr[NUM_OF_ELEMENTS];
	for(int i=0;i<NUM_OF_ELEMENTS;i++)
		sortedArr[i]=arr[i];
	clock_t startTime = clock();
	for(int i=0;i<NUM_OF_ELEMENTS; i++)
		for (int j=i; j<NUM_OF_ELEMENTS; j++)
			if(comparator(&sortedArr[i], &sortedArr[j]) == 1)
			{
				int buf=sortedArr[i];
				sortedArr[i]=sortedArr[j];
				sortedArr[j]=buf;
			}
	clock_t endTime = clock();
	return (endTime-startTime);
}

clock_t getQuickSortTime (int* array)
{
	clock_t startQuick = clock();
	qsort((void*)array, NUM_OF_ELEMENTS, sizeof(int), comparator);
	clock_t endQuick = clock();
	return endQuick - startQuick;
}

void print(int* array)
{
	for (int i=0;i<NUM_OF_ELEMENTS;i++)
		printf("%d ", array[i]);
	printf("\n");
}

void getArray(int* array)
{
	for (int i=0;i<NUM_OF_ELEMENTS;i++)
		scanf("%d", &array[i]);
}

int main()
{
	int array[NUM_OF_ELEMENTS]; 
	getArray(array);
	clock_t bubbleTime = getBubbleSortTime(array);
	clock_t quickTime = getQuickSortTime(array);
	print(array);
	printf("%d\n%d", bubbleTime, quickTime);
}