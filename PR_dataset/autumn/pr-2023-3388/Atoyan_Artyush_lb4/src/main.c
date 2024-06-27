#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*#define N 5*/

int cmp_by_abs(const void* p, const void* q){
	const int* pi = (const int*)p;
	const int* qi = (const int*)q;
	if(abs(*pi) > abs(*qi)){
		return -1;
	}
	else if(*pi == *qi){
		return 0;
	}
	else{
		return 1;
	}
}

float time_of_sort(int a[], int N)
{
    time_t start = clock();
	qsort(a, N, sizeof(int), cmp_by_abs);
	time_t finish = clock();
	for(int k = 0; k < N; ++k){
		fprintf(stdout, "%d", a[k]);
		if(k < N-1){
			fprintf(stdout, " ");
		}
		else{
			fprintf(stdout, "\n");
		}
	}
	return 1.0*(finish-start)/CLOCKS_PER_SEC;
	
}

int main(void){
    int N = 1000;
	int a[N];
	for(int k = 0; k < N; ++k){
		fscanf(stdin, "%d", &a[k]);
	}
	
	fprintf(stdout, "%lf\n", time_of_sort(a, N));
	return 0;	
}
