#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define SIZE_OF_ARRAY 1000

void input(int* array){
    char new_char;

    for(int i = 0; i < SIZE_OF_ARRAY; i++){
        scanf("%d", &array[i]);
        scanf("%c", &new_char);
    }
}

int comparator(const void* a,const void* b){
    return (*(int*)a) >= (*(int*)b);
}

void bubblesort(int* array){
    int temp;
    for(int i = SIZE_OF_ARRAY - 1; i >= 0; i--){
        for(int j = 1; j <= i; j++){
            if (comparator(&array[j-1], &array[j])){
                temp = array[j-1];
                array[j-1] = array[j];
                array[j] = temp;
            }
        }
    }
}

void output(int* array, int time_of_bubblesort, int time_of_qsort){
    for(int i = 0; i < SIZE_OF_ARRAY; i++){
        printf("%d ", array[i]);
    }
    printf("\n%f\n%f", time_of_bubblesort / CLOCKS_PER_SEC, time_of_qsort / CLOCKS_PER_SEC);
}


int main(){
    int array[SIZE_OF_ARRAY];
    int time_of_bubblesort, time_of_qsort;

    input(array);
    int array_to_sort[SIZE_OF_ARRAY];
    memcpy(array_to_sort, array, sizeof(int)*SIZE_OF_ARRAY);
    
    time_of_bubblesort = clock();
    bubblesort(array_to_sort);
    time_of_bubblesort = clock() - time_of_bubblesort;


    time_of_qsort = clock();
    qsort(array, SIZE_OF_ARRAY, sizeof(int), comparator);
    time_of_qsort = clock() - time_of_qsort;
    
    output(array_to_sort, time_of_bubblesort, time_of_qsort);

    return 0;
}
