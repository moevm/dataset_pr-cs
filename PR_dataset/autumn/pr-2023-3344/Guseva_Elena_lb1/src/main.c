
#include <stdio.h>
#include <stdlib.h>

int index_first_zero(int array[], int size){
    for (int i=0; i<size; i++){
        if (array[i]==0){
            return i;
        }
    }
    return -1;
}

int index_last_zero(int array[], int size){
    for (int i=size-1; i>=0; i--){
        if (array[i]==0){
            return i;
        }
    }
    return -1;
}

int sum_between(int array[], int size){
    int sum=0;
    int indx_1_0=index_first_zero(array, size);
    int indx_last_0=index_last_zero(array, size);
    for (int i=indx_1_0; i<=indx_last_0; i++){
        sum=sum+abs(array[i]);
    }
    return sum;
}

int sum_before_and_after(int array[], int size){
    int sum=0;
    for (int i=0; i<size; i++){
        sum=sum+abs(array[i]);
    }
    sum=sum-sum_between(array, size);
    return sum;
}

int main(){
    int a;
    int size=0;
    int array[100];
    scanf("%d", &a); 
    while (scanf("%d", &array[size])==1){ 
        size++;
        if (getchar()=='\n'){ 
            break;
        }
    }

   

    switch(a){
        case 0:
            printf("%d\n", index_first_zero(array, size));
            break;
        case 1:
            printf("%d\n", index_last_zero(array, size));
            break;
        case 2:
            printf("%d\n", sum_between(array, size));
            break;
        case 3:
            printf("%d\n", sum_before_and_after(array, size));
            break;
        default:
            printf("Данные некорректны \n");
            break;
    }
    return 0;
} 
