#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>


int cmps(const void* a, const void* b) {
	return *(const int*)a > *(const int*) b;
}

int cmpbs(const void* a, const void* b) {
	const int* f = (const int*) a;
	const int* s = (const int*) b;
	if (*f > *s){
        	return 1;
    	}
    	if (*f < *s){
        	return -1;
    	}
    	return 0;
}

int main(){
	int n = 1000;
	int* arr = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	qsort(arr, n, sizeof(int), cmps);
	clock_t t = clock();
	int k = 0;
	int* res = bsearch(&k, arr, n, sizeof(int), cmpbs);
	if(res) puts("exists\n");
	else puts("doesn't exist\n");
	printf("%ld\n", (clock() - t)/CLOCKS_PER_SEC);
	t = clock();
	int f = 0;
	for (int i = 0; i < n; i++) {
		if (arr[i] == 0) {
			f = 1;
		}
	}
	if(f) puts("exists\n");
	else puts("doesn't exist\n");
	printf("%ld\n", (clock() - t)/CLOCKS_PER_SEC);
}
