#include <stdio.h>
#include <limits.h>
#define ARRAY_LENGTH 100

int get_max(int array[], int length)
{
    int max = INT_MIN;
    for(int i = 0; i<length; i++)
    {
        if (array[i]>max)
        {
            max = array[i];
        }
    }
    return max;
}

int get_min(int array[], int length)
{
    int min = INT_MAX;
    for(int i = 0; i<length; i++)
    {
        if (array[i]<min)
        {
            min = array[i];
        }
    }
    return min;
}

int get_diff(int array[], int length)
{
    return get_max(array,length) - get_min(array,length);
}

int get_sum(int min,int array[])
{
    int i = 0;
    int sum = 0;
    while(array[i] != min)
    {
        sum+=array[i];
        i++;
    }
    return sum;
}

void show_answer(int ans)
{
    if (ans == INT_MIN)
        printf("Данные некорректны\n");
    else
        printf("%d\n", ans);
}

void read_array(int array[], int *value, int *length)
{
    scanf("%d",value);
    int i = 0;
    while(getchar()!='\n')
    {
        scanf("%d",&array[i]);
        i++;
        (*length)++;
    }
}

void choose_answer(int value, int array[], int length)
{
    switch (value)
    {
    case 0:
        show_answer(get_max(array,length));
        break;
    case 1:
        show_answer(get_min(array,length));
        break;
    case 2:
        show_answer(get_diff(array,length));
        break;
    case 3:
        show_answer(get_sum(get_min(array,length),array));
        break;
    default:
        show_answer(INT_MIN);
        break;
    }
}

int main()
{
    int array[ARRAY_LENGTH];
    int value = 0, length = 0;
    read_array(array,&value,&length);
    choose_answer(value, array, length);
    return 0;
}