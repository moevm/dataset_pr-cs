# include <stdio.h>
# include <stdlib.h>
# include <time.h>

int cmp(const void * a, const void * b){
    const int * one = (const int * )a;
    const int * two = (const int * )b;
    if (* one > * two){
        return 1;
    }
    if (* one < * two){
        return -1;
    }
    return 0;
}

void sort_bubble(int array[], int N){
    for (int i = N - 1; i >= 0; i--){
        for (int j = 1; j < i; j++){
            if (array[j] <= array[j - 1]){
                int current = array[j - 1];
                array[j - 1] = array[j];
                array[j] = current;
            }
        }
    }
}

double time_spend(clock_t start, clock_t end){
    return (double) (end - start) / CLOCKS_PER_SEC;
}

int main(){
    int array[1000];
    int N = sizeof(array)/sizeof(int);

    for (int i = 0; i < 1000; i++){
        scanf("%d ", &array[i]);
    }

    clock_t bubble_start, bubble_end;
    double time_bubble_sort;
    bubble_start = clock();
    sort_bubble(array, N);
    bubble_end = clock();
    time_bubble_sort = time_spend(bubble_start, bubble_end);

    clock_t q_start, q_end;
    double time_qsort;
    q_start = clock();
    qsort(array, N, sizeof(int), cmp);
    q_end = clock();
    time_qsort = time_spend(q_start, q_end);

    for (int i = 0; i < 1000; i++){
        printf("%d ", array[i]);
    }

    printf("\n");
    printf("%f\n", time_bubble_sort);
    printf("%f\n", time_qsort);
}