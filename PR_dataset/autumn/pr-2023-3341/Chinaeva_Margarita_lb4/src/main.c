#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

void input(int arr[SIZE]);
int cmp(const void* a, const void* b);
void search_null_bsearch(int arr[SIZE]);
void search_null_iterate(int arr[SIZE]);
void time_bsearch(int arr[SIZE]);
void time_iterate(int arr[SIZE]);

int main() {
	int arr[SIZE];
	input(arr);
	qsort(arr, SIZE, sizeof(int), cmp);
	time_bsearch(arr);
	time_iterate(arr);
	return 0;
}

void input(int arr[SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		scanf("%d", &arr[i]);
	}
}

int cmp(const void* a, const void* b) {
	if (*(int*)a > *(int*)b)
		return 1;
	if (*(int*)a < *(int*)b)
		return -1;
	return 0;
}

void search_null_bsearch(int arr[SIZE]) {
	int null = 0;
	int* index_null = bsearch(&null, arr, SIZE, sizeof(int), cmp);
	if (index_null)
		printf("exists\n");
	else printf("doesn't exist\n");
}

void search_null_iterate(int arr[SIZE]) {
	int check = 0;
	for (int i = 0; i < SIZE; i++) {
		if (arr[i] == 0)
			check = 1;
	}
	if (check)
		printf("exists\n");
	else printf("doesn't exist\n");
}

void time_bsearch(int arr[SIZE]) {
	clock_t start_bsearch = clock();
	search_null_bsearch(arr);
	clock_t end_bsearch = clock();
	double time = ((double)(end_bsearch - start_bsearch)) / CLOCKS_PER_SEC;
	printf("%f\n", time);
}

void time_iterate(int arr[SIZE]) {
	clock_t start_iterate = clock();
	search_null_iterate(arr);
	clock_t end_iterate = clock();
	double time = ((double)(end_iterate - start_iterate)) / CLOCKS_PER_SEC;
	printf("%f\n", time);
}
