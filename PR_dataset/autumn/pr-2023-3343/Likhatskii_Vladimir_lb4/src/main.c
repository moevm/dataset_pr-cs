#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ARR_SIZE 1000
#define SEARCH_FUNCTIONS_COUNT 2

typedef void* (*search[SEARCH_FUNCTIONS_COUNT])();

void scan_int_array(int* arr) {
    for(int i = 0; i < ARR_SIZE; i++) {
        scanf("%d", &arr[i]);
    }
}

int compare(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

/** 
*  Linear analog of bsearch, works with sorted arrays
*/
void* ssearch(const void *__key, const void *__base, size_t __nmemb, size_t __size, __compar_fn_t __compar) {
    char *base = (char *)__base;
    void *p;
    int cmp;  

    for(int i = 0; i < __nmemb; i++) {
        p = base + (i * __size);
        cmp = (*__compar)(__key, p); 

        if(cmp == 0) {
            return p; 
        }
        if(cmp < 0) {
            return (NULL);
        }
    }

    return (NULL);
}

int main() {
    int arr[ARR_SIZE]; 
    scan_int_array(arr);
    qsort(arr, ARR_SIZE, sizeof(int), compare);

    search s = { bsearch, ssearch };

    int key = 0; 

    for(int i = 0; i < SEARCH_FUNCTIONS_COUNT; i++) {
        time_t start = clock(); 
        int* exists = (*s + i)(&key, arr, ARR_SIZE, sizeof(int), compare);
        time_t delta = clock() - start; 

        if(exists) {
            printf("exists\n");
        } else {
            printf("doesn't exist\n");
        }

        printf("%ld\n", delta);
    }

    return 0; 
}