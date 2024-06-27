#include <stdio.h>
#include <stdlib.h>

int index_first_zero(int* arr, int l){
    int i=0;
    while(arr[i]!=0 && i<l)
        i++;
        return i;
}

int index_last_zero(int* arr, int l){
    int i=l-1;
    while(arr[i]!=0 && i>0)
    i--;
        return i;
}

int sum_between(int* arr,int l){
        int first = index_first_zero(arr,l);
        int last = index_last_zero(arr,l);
        int sum = 0;
        for(int i = first;i < last;i++)
                sum += abs(arr[i]);
        return sum;
} 

int sum_before_and_after(int* arr, int l){
        int first = index_first_zero(arr,l);
        int last = index_last_zero(arr,l);
        int sum1 = 0;
        int sum2 = 0;
        for(int i = 0;i < first;i++)
                sum1 += abs(arr[i]);
        for(int i = last;i < l;i++)
                sum2 += abs(arr[i]);
        int sum = sum1 + sum2;
        return sum;
}

int main(){
        int arr[100];
        int i = 0;
        int l;
        int cmd;
        scanf("%d", &cmd);
        char slashN;
        do{
                scanf("%d%c", &arr[i], &slashN);
                i++;
        }
        while(slashN != '\n' && i < 100);
                l = i;
                if(index_last_zero(arr,l) != -1)
                        switch(cmd){
                                case 0:
                                        {printf("%d\n", index_first_zero(arr,l));
                                        break;}
                                case 1:
                                        {printf("%d\n", index_last_zero(arr,l));
                                        break;}
                                case 2:
                                        {printf("%d\n", sum_between(arr,l));
                                        break;}
                                case 3:
                                        {printf("%d\n", sum_before_and_after(arr,l));
                                        break;}
                                default:
                                        printf("Данные некорректны\n");
                        }
                else
                        printf("Данные некорректны");
}
