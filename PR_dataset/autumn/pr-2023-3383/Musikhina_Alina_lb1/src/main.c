#include <stdio.h>
#include <stdlib.h>


int index_first_negative(int mas[], int ln){
    int indperv;
    for (int i=0; i<ln; i++)
    {
        if (mas[i] < 0){
            indperv=i;
            break;
        }
    }
    return indperv;
}



int index_last_negative(int mas[], int ln){
    int indposl;
    for (int i=ln-1; i>=0; i--)
    {
        if (mas[i] < 0)
    {       indposl=i;
            break;
        }
        
    }
    return indposl;
}



int sum_between_negative(int mas[], int ln, int indperv, int indposl){
    int s=0;
    for (int i=indperv; i<indposl; i++)
    {
        s+=abs(mas[i]);
    }
    return s;
}



int sum_before_and_after_negative(int mas[], int ln, int indperv, int indposl){
    int d = 0;
    for (int i=0; i<ln; i++)
    {
       d+=abs(mas[i]); 
    }
    return d - sum_between_negative(mas, ln, indperv, indposl);
}



int main()
{
    int number;
    scanf("%d", &number);
    int mas[100];
    int i=-1;
    while (getchar()!='\n'){
        i++;
        if (i==100){
            puts("Данные некорректны\n");
            return 0;
        }
        scanf("%d", &mas[i]);
    }
    int ln = i+1;
    switch (number){
        case 0:
            printf("%d\n",index_first_negative(mas, ln));
            break;
        case 1:
            printf("%d\n",index_last_negative(mas, ln));
            break;
        case 2:
            printf("%d\n",sum_between_negative(mas, ln, index_first_negative(mas, ln), index_last_negative(mas, ln)));
            break;
        case 3:
            printf("%d\n",sum_before_and_after_negative(mas, ln, index_first_negative(mas, ln), index_last_negative(mas, ln)));
            break;
        default:
            puts("Данные некорректны\n");
    }
    
}
