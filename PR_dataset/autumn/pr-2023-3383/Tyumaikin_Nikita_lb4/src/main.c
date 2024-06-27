#include <stdio.h>
#include <stdlib.h>
#include <time.h>   
#define SIZE 1000

int comp(const void *, const void *);

int main(){
    int array[SIZE]; 
    clock_t t;
    int key = 0;
    int found = 0;
    
    for(int i =0; i < SIZE; i++){
        scanf("%d", &array[i]);
    }
    
    qsort(array, SIZE, sizeof(int), comp);
    
    t = clock();
    int *ptr = (int*)bsearch(&key, array, SIZE, sizeof(int), comp);
    if (ptr){
        puts("exists");
    }
    else{
       puts("doesn't exist");
    }
    t = clock() - t;
    printf("%f\n", (float)t/CLOCKS_PER_SEC);
    
    t = clock();
    for(int i = 0; i < SIZE; i++){
        if(array[i] == 0){
            found = 1;
        }
    }
    if(found == 1){
        puts("exists");
    }
    else{
        puts("doesn't exist");
    }
    t = clock() - t;
    printf("%f\n", (float)t/CLOCKS_PER_SEC);
    
    return 0;
    
}

int comp(const void *i, const void *j){
  return *(int *)i - *(int *)j;
}
