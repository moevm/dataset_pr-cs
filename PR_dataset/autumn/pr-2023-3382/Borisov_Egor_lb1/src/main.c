#include <stdio.h>
#include <stdlib.h>

int index_first_zero(int massive[], int i, int len)
{
    int zero_f = 0;
    for(i = 0; i < len; i++)
    {
        if((massive[i]) == 0)
        {
            zero_f = i;
            return zero_f;
            break;
        }
    }
}

int index_last_zero(int massive[], int i, int len)
{
    int zero_l = 0;
    for(i = 0; i < len; i++)
    {
        if((massive[i]) == 0)
        {
            zero_l = i;

        }
    }
    return zero_l;
}

int sum_between(int massive[], int i, int len)
{
    int sum_b = 0;
    int lower = index_first_zero(massive, i, len);
    int upper = index_last_zero(massive, i, len);
    for(i = lower; i < upper; i++)
    {
        sum_b += abs(massive[i]);
    }
    return sum_b;
}


int sum_before_and_after(int massive[], int i, int len)
{
    int sum_b_a = 0;
    int lower = index_first_zero(massive, i, len);
    int upper = index_last_zero(massive, i, len);
    for(i = 0; i < lower; i++)
    {
        sum_b_a += abs(massive[i]);
    }
    for(i = upper; i < len; i++)
    {
        sum_b_a += abs(massive[i]);
    }
    return sum_b_a;
}

int main()
{
    int operation;
    int massive[100];
    int i = 0;
    int answer = 0;
    char space;
    int len = 0;
    scanf("%d%c", &operation, &space);
    do
    {
        scanf("%d%c", &massive[len], &space);
        len++;
    } while(space != '\n');
    
    switch(operation){
        case 0:
            answer = index_first_zero(massive, i, len);
            printf("%d", answer);
            break;
        case 1:
            answer = index_last_zero(massive, i, len);
            printf("%d", answer);
            break;
        case 2:
            answer = sum_between(massive, i, len);
            printf("%d", answer);
            break;
        case 3:
            answer = sum_before_and_after(massive, i, len);
            printf("%d", answer);
            break;
        default:
            puts("Данные некорректны");
    }
    return 0;
}