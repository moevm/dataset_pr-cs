#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define BUFFER 100500   // Размер буфера под ввод
#define N 1000          // Размер массива


// Функция для сравнения чисел
int compare(const void * a, const void * b)
{
    return( *(int*)a -  *(int*)b );
}


int main()
{
    // Считывание ввода
    char input[BUFFER];
    fgets(input, BUFFER, stdin);
    char * p = input;
    
    // Получение и сортировка массива чисел
    int nums[N];
    int i;
    for(i = 0; i < N; i++)
    {
        nums[i] = strtol(p, &p, 10);
    }
    qsort((void*)nums, N, sizeof(int), compare);

    // определение искомого числа
    int search_target = 0;

    // Метод двоичного поиска
    clock_t start = clock();
        void * bin_res = (int*)bsearch(&search_target, (void*)nums, N, sizeof(int), compare);
    clock_t end = clock();
    if(bin_res == NULL)
    {
        printf("doesn't exist\n");
    }
    else
    {
        printf("exists\n");
    }
    printf("%f\n", (float)(end-start) / CLOCKS_PER_SEC);

    // Метод переборного поиска
    start = clock();
        char bf_res = 0;
        for(i = 0; i < N; i++)
        {
            if(nums[i] == search_target)
            {
                bf_res = 1;
                break;
            }
        }
    end = clock();
    if(bf_res)
    {
        printf("exists\n");
    }
    else
    {
        printf("doesn't exist\n");
    }
    printf("%f\n", (float)(end-start) / CLOCKS_PER_SEC);

    return 0;
}
