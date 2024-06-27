#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int cmp(const void* a, const void* b) {
	const int* first = (const int*)a;
	const int* second = (const int*)b;

	if (*first > *second)
		return 1;
	if (*first < *second)
		return -1;
	return 0;
}

int main(void) {
	int mas[1000];
	clock_t start, end;
	int count = 0;

	for (int i = 0; i < sizeof(mas) / sizeof(mas[0]); i++) {
		scanf("%d", &mas[i]);
	}

	qsort(mas, sizeof(mas) / sizeof(mas[0]), sizeof(mas[0]), cmp);

	int key = 0;
	start = clock();

	if (bsearch(&key, mas, sizeof(mas) / sizeof(mas[0]), sizeof(mas[0]), cmp))
		puts("exists");
	else
		puts("doesn't exist");

	end = clock();
	printf("%ld\n", (end - start));

	start = clock();
	for (int i = 0; i < sizeof(mas) / sizeof(mas[0]); i++) {
		if (key == mas[i]) {
			count++;
			puts("exists");
		}
	}
	if (count == 0) {
		puts("doesn't exist");
	}

	end = clock();
	printf("%ld\n", (end - start));

	return 0;
}
