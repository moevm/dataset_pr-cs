#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#define N 1000
#define TRUE "exists\n"
#define FALSE "doesn't exist\n"
int cmp(const void* next, const void* previous)
{
	const int* first = (const int*)next;
	const int* second = (const int*)previous;
	if (*first > *second)
		return 1;
	if (*first < *second)
		return -1;
	return 0;
}
void input(int arr[]) {
	for (int i = 0; i < N; i++)
		scanf("%d\n", &arr[i]);
}
void process_first(int arr[]) {
    clock_t start, time;
    start = clock();
	qsort(arr, N, sizeof(int), cmp);
	int key = 0;
	int* res = bsearch(&key, arr, N, sizeof(int), cmp);
	if (res)
		printf(TRUE);
	else
		printf(FALSE);
	time = clock() - start;
	printf("%f\n", ((float)time));
	
}
void process_second(int arr[]) {
    clock_t start, time;
    start = clock();
	int flag = 0;
	for (int j = 0; j < N; j++) {
		if (arr[j] == 0) {
			flag = 1;
			break;
		}
	}
	if (flag == 1)
		printf(TRUE);
	else
		printf(FALSE);
	time = clock() - start;
	printf("%f\n", ((float)time));
}
int main() {
	int arr[N];
	input(arr);
	process_first(arr);
	process_second(arr);
}