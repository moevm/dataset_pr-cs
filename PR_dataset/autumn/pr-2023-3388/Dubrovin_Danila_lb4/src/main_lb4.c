#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

#define MAS_INPUT_SIZE 1000000
#define MAS_OUTPUT_SIZE 1000


/*Компаратор*/
int compare(const void *element_1, const void *element_2)
{
    const int *first = (const int *)element_1;
    const int *second = (const int *)element_2;
    if (*first > *second) {
        return -1;
    }
    if (*first < *second) {
        return 1;
    }
    return 0;
}


/*Считывание данных*/
void read_input(char *input, int *numbers, int *num_count)
{
    fgets(input, MAS_INPUT_SIZE, stdin);
    char *token = strtok(input, " ");
    while (token != NULL && *num_count < MAS_OUTPUT_SIZE) {
        numbers[*num_count] = atoi(token);
        (*num_count)++;
        token = strtok(NULL, " ");
    }
}


/*Быстрая сортировка*/
void quick_sort_and_time(int *numbers, int num_count, double *time_spent){
    clock_t begin = clock();
    qsort(numbers, num_count, sizeof(int), compare);
    clock_t end = clock();
    *time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
}


/*Вывод ответа*/
void print_answer(int *numbers, int num_count, double time_spent)
{
    for (size_t i = 0; i < num_count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    printf("%f ", time_spent);
}


int main()
{
    double time_spent = 0.0;
    char *input = malloc(MAS_INPUT_SIZE);
    int *numbers = calloc(sizeof(int), MAS_OUTPUT_SIZE); 
    int num_count = 0;

    read_input(input, numbers, &num_count);
    quick_sort_and_time(numbers, num_count, &time_spent);
    print_answer(numbers, num_count, time_spent);

    free(input);
    free(numbers);

    return 0;
}