#include <stdio.h>
#include <stdlib.h>
int SUMALL = 0;
int indFirst(int arr[],int k){
    for(int i = 0; i < k;i++){
        if(arr[i]%2 == 0){
            return i;
        }
    }
    return -1;
}
int indLast(int arr[],int k){
    for(int i = k-1; i >=0;i--){
        if(arr[i]%2 != 0){
            return i;
        }
    }
    return -1;
}
void func(int num, int arr[], int k){
    int first = indFirst(arr,k),last = indLast(arr,k);
    if(num == 0){
        printf("%i\n",first);
    }
    else if(num == 1){
        printf("%i\n", last);
    }
    else if(num == 2 | num == 3){
        int sum = 0;
        for(int i = first; i < last;i++){
            sum += abs(arr[i]);
        }
        if(num == 2){
            printf("%i\n",sum);
        }
        else{
            printf("%i\n",SUMALL - sum);
        }
    }
    else{
        printf("%s\n","Данные некорректны");
    }
}
int main()
{
    int k = 0,num,z;
    int arr[100];
    scanf("%i",&num);
    while(scanf("%i",&z) == 1){
        SUMALL += abs(z);
        arr[k] = z;
        k++;
    }
    func(num,arr,k);
    return 0;
}
