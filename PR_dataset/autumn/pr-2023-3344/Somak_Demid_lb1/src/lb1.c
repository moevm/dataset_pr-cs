#include <stdio.h>
#include <stdlib.h>

int first_zero(int M[],int end){
    int indfrs;
    for(int i = 0;i < end;i++){
        if(M[i] == 0){
            indfrs = i;
            break;
        }
    }
    return indfrs;
}

int last_zero(int M[],int end){
    int indlast;
    for(int i = 0;i < end;i++){
        if(M[i] == 0){
            indlast = i;
        }
    }
    return indlast;
}

int sum_beetwen(int M[],int frst,int end){
    int sum = 0;
    for(int i = frst;i < end;i++){
        sum += abs(M[i]);
        }
    return sum;
}

int sum_before_after(int M[],int frst,int frst2,int end ){
    int sum = 0;
    for(int i = 0;i < frst;i++){
        sum += abs(M[i]);
        }
    for(int i = frst2;i < end;i++){
        sum += abs(M[i]);
        }
    return sum;
}

int main(){
    int a,arr[100],ch;
    scanf("%d",&a);
    int n = 0;
    for(int i = 0; ((ch = getchar()) != '\n'); i++){
            scanf("%d",&arr[i]);
            n++;
        }
    switch(a){
            case 0:
                printf("%d\n", first_zero(arr,n));
                break;
            case 1:
                printf("%d\n", last_zero(arr,n));
                break;
            case 2:
                printf("%d\n", sum_beetwen(arr,first_zero(arr,n),last_zero(arr,n)));
                break;
            case 3:
                printf("%d\n", sum_before_after(arr,first_zero(arr,n),last_zero(arr,n),n));
                break;
            default:
                puts("Данные некорректны");
    };
}
