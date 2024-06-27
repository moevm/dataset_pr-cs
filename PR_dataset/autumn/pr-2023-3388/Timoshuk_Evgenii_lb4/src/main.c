#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 
#define LEN 1000

int cmp(const void *a, const void *b)
{
    const int *f = (const int *)a;
    const int *s = (const int *)b;
    if(abs(*f)<abs(*s))
    {
        return 1;
    }
    if(abs(*f)>abs(*s))
    {
        return -1;
    }
    return 0;
}

void input_array(int array[], int *count)
{
    *count = 0;
    do
    {
        if(*count<LEN)
        {
            scanf("%d", &array[*count]);
            (*count)++;
        }
        
    }
    while(getchar() != '\n');
}

void sort_and_print(int array[], int count)
{
    double time_spent = 0.0;
    clock_t start_time = clock();
    qsort(array, count, sizeof(int), cmp);
    for(int i = 0; i<count; i++)
    {
        printf("%d ", array[i]);
    }
    clock_t end_time = clock();
    time_spent += (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("\n%f", time_spent);
}

int main()
{
    int count;
    int array[LEN];
    
    input_array(array, &count);
    
    sort_and_print(array, count);
    
    return 0;
}