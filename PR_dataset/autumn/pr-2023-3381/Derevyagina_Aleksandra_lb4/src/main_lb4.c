#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000

int cmp(const void *a, const void *b){
	const int *f = (int *)a;
	const int *s = (int *)b;
	if (abs(*f) > abs(*s)){
		return -1;
	}
	if (abs(*f) < abs(*s)){
		return 1;
	}
	return 0;
}

int main(){
	int arr[N];
	for (int i = 0; i < N; i++){
		scanf("%d", &arr[i]);
	}
	clock_t start, stop;
	start = clock ();
	qsort(arr, N, sizeof(int), cmp);
	stop = clock();
	for (int i = 0; i < N; i++){
		printf("%d ", arr[i]);
	}
	printf("\n%ld\n", (stop - start));
	return 0;
}
