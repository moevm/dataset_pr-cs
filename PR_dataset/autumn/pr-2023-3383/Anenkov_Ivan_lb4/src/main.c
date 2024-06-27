#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp(const void * a, const void * b) {
	int X = *(int*) a;
	int Y = *(int*) b;
	return (X - Y);
}

int main () {
	int maxN = 1000;
	int * arr = malloc(maxN * sizeof(int));

	int num = 0;
	char enter;
	while (num < maxN && enter != '\n'){
		scanf("%d%c", &arr[num], &enter);
		num++;
	}


	int ch = 0;
	clock_t start_bubble, stop_bubble;
	start_bubble = clock ();
	for (int i = 0; i < num; i++) {
		for (int j = i+1; j < num; j++) {
			if (arr[i] >= arr[j]) {
				ch = arr[i];
				arr[i] = arr[j];
				arr[j] = ch;
			}
		}
	}
	stop_bubble = clock();
	double time_used_bubble = ((double)(stop_bubble - start_bubble)) / CLOCKS_PER_SEC;


	clock_t start_quick, stop_quick;
	start_quick = clock();
	qsort(arr, num, sizeof(int), cmp);
	stop_quick = clock();
	double time_used_quick = ((double)(stop_quick - start_quick)) / CLOCKS_PER_SEC;


	for (int i = 0; i < num; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	printf("%f\n", time_used_bubble);
	printf("%f\n", time_used_quick);

	free(arr);
	return 0;
}