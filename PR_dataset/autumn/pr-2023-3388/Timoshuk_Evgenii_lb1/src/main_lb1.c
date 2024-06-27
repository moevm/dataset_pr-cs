#include <stdio.h>
#include <stdlib.h>
#define N 101
#define P "%d\n"


int index_first_negative(int array[], int count)
{
    
    for(int i = 1; i<count; i++)
    {
        if(array[i] < 0)
        {
            return i-1;
            break;
        } 
        
    }
    return -1;
}
int index_last_negative(int array[], int count)
{
    
    for(int i = count -1; i>0; i--)
    {
        if(array[i] < 0)
        {
            return i-1;
            break;
        } 
    } 
    return -1;
}
int sum_between_negative(int array[], int count)
{
    int sum = 0;
    for(int i = index_first_negative(array, count)+1; i<index_last_negative(array, count)+1; i++)
    {
        sum += abs(array[i]);
    }
    return sum;
}
int sum_before_and_after_negative(int array[], int count)
{
    int sum_before_negative = 0;
    int sum_after_negative = 0;
    for(int i = 1; i<index_first_negative(array, count)+1; i++)
    {            
        sum_before_negative += array[i];      
    }
    for(int i = count; i > index_last_negative(array, count)+1; i--)
    {            
        sum_after_negative += abs(array[i-1]);      
    }
    return sum_before_negative + sum_after_negative;   
}
void call_operation(int array[], int count)
{
    switch(array[0])
    {
        case 0:
            printf(P, index_first_negative(array, count));
            break;
        case 1:
            printf(P, index_last_negative(array, count));
            break;
        case 2:
            printf(P, sum_between_negative(array, count));
            break;
        case 3:
            printf(P, sum_before_and_after_negative(array, count));
            break;
        default:
            printf("Данные некорректны\n");
    }   

}

int main()
{
    
    int count = 0;
    int array[N];
     do
    {
        if(count<N)
        {
        scanf("%d", &array[count]);
        count++;
        }
        else
        {
            return 0;
        }
    }
    while(getchar() != '\n');
    call_operation(array, count);
    
    
    
    return 0;  
}