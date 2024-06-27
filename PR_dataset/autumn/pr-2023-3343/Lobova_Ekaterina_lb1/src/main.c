#include <stdio.h>
#include <stdlib.h>

int index_first_zero(int a[], int n){
    for (int i=0;i<n;i++){
        if (a[i]==0){
            return i;
        }
    }
}

int index_last_zero(int a[], int n){
    for (int i=n-1;i>=0;i--){
        if (a[i]==0){
            return i;
        }
    }
}

long sum_between(int a[], int n){
    int i_first=index_first_zero(a,n);
    int i_last=index_last_zero(a,n);
    long sum=0;
    for (int i=i_first;i<=i_last;i++){
        sum+=abs(a[i]);
    }
    return sum;

}

long sum_before_and_after(int a[], int n){
    int i_first=index_first_zero(a,n);
    int i_last=index_last_zero(a,n);
    long sum=0;
    for (int i=0;i<i_first;i++){
        sum+=abs(a[i]);
    }
    for (int i=i_last+1;i<n;i++){
        sum+=abs(a[i]);
    }
    return sum;
}
int main()
{
    int action;
    scanf("%i",&action);
    int array[100];
    int len_array=0;
    while (getchar()!='\n'){
        scanf("%i",&array[len_array]);
        len_array++;
    }
    switch(action){
    case 0:
        printf("%i", index_first_zero(array,len_array));
        break;
    case 1:
        printf("%i", index_last_zero(array,len_array));
        break;
    case 2:
        printf("%li", sum_between(array,len_array));
        break;
    case 3:
        printf("%li", sum_before_and_after(array,len_array));
        break;
    default:
        printf("Данные некорректны");
    }
    return 0;
}

