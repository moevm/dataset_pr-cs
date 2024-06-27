#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

void input(const int* numbers){
    for (int i = 0; i < SIZE; i++){
        scanf("%d", &numbers[i]);
    }
}
int comporator(const void* start, const void* end){
    return ( * (int *)end - * (int *)start);
}
double time_sort(double start_time, double end_time){
        double passed_time = start_time - end_time;
    return passed_time;
}
void output(const int* numbers, double start_time, double end_time){
    for (int i = 0; i < SIZE; i++){
        printf("%d ", numbers[i]);
    }
    double passed_time = time_sort(start_time, end_time);
    printf("\n%f", passed_time);
}
int main(){
    int numbers[SIZE];
    input(numbers);
    double start_time = clock();
    qsort(numbers, SIZE, sizeof(int), comporator);
    double end_time = clock();
    output(numbers, start_time, end_time);
}
