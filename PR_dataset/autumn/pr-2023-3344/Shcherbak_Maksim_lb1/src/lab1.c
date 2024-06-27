#include <stdio.h>
#define mas 20
int index_first_negative(int a[], int count)
{
    for(int i=0; i<count;i++)
    {
        if (a[i]<0)
        {
            return i;
        }
    }
    return -1;
}
int index_last_negative(int a[], int count)
{
    int last;
    for(int i=0; i<count; i++)
    {
        if (a[i]<0)
        {
            last=i;
        }
    }
    return last;
}
int multi_between_negative(int a[], int count)
{
    int first = index_first_negative(a, count);
    int last = index_last_negative(a, count);
    int start=1;
    for(int i=first; i<last; i++)
    {
        start*=a[i];
    }
    return start;
}
int multi_before_and_after_negative(int a[], int count)
{
    int first = index_first_negative(a, count);
    int last = index_last_negative(a, count);
    int start=1;
    for(int i=0; i<first; i++)
    {
        start*=a[i];
    }
    for(int i=last; i<count; i++)
    {
        start*=a[i];
    }
    return start;
}
int main()
{
    int a[mas];
    int data;
    int count=0;
    char other;
    scanf("%d", &data);
  while(count<mas){
        scanf("%d", &a[count]);
        count++;
        if (getchar() == '\n'){
            break;
        }
    }
    switch (data)
    {
    case 0:
        printf("%d\n", index_first_negative(a, count));
        break;
    case 1:
        printf("%d\n", index_last_negative(a, count));
        break;
    case 2:
        printf("%d\n", multi_between_negative(a, count));
        break;
    case 3:
        printf("%d\n", multi_before_and_after_negative(a, count));
        break;
    default:
        printf("Данные некорректны\n");

    }
    return 0;
}
