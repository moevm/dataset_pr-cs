#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MEMORY 4000 // Размер буфера 
#define N 1000  // Размер массива


// Функция для сравнения чисел
int cmp(const void * a, const void * b)
{
    return( *(int*)a -  *(int*)b );
}

// Функция для считывания ввода
char* getInput()
{
    char scan[MEMORY];
    fgets(scan, MEMORY, stdin);
    char * p = scan;
    return p;
}

// Функция для получения и сортировки массива чисел
void qSort(int *nums, char *input)
{
    int i;
    for(i = 0; i < N; i++)
    {
        nums[i] = strtol(input, &input, 10);
    }
    qsort((void*)nums, N, sizeof(int), cmp);
}

// Функция для двоичного поиска
void binarySearch(int *nums, int find_number)
{
    clock_t start = clock();
    void * result_bs = (int*)bsearch(&find_number, (void*)nums, N, sizeof(int), cmp);
    clock_t end = clock();
    if(result_bs == NULL)
    {
        printf("doesn't exist\n");
    }
    else
    {
        printf("exists\n");
    }
    printf("%f\n", (float)(end-start) / CLOCKS_PER_SEC);
}

// Функция для переборного поиска
void bruteForceSearch(int *nums, int find_number)
{
    clock_t start = clock();
    int result_bfs = 0;
    for(int i = 0; i < N; i++)
    {
        if(nums[i] == find_number)
        {
            result_bfs = 1;
            break;
        }
    }
    clock_t end = clock();
    if(result_bfs)
    {
        printf("exists\n");
    }
    else
    {
        printf("doesn't exist\n");
    }
    printf("%f\n", (float)(end-start) / CLOCKS_PER_SEC);
}

int main()
{
    // Считывание ввода
    char *p = getInput();
    
    // Получение и сортировка массива чисел
    int nums[N];
    qSort(nums, p);

    // Определение искомого числа
    int find_number = 0;

    // Метод двоичного поиска
    binarySearch(nums, find_number);

    // Метод переборного поиска
    bruteForceSearch(nums, find_number);

    return 0;
}
