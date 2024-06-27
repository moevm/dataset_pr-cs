//var6
#include <stdio.h>
#include <stdlib.h>

#define N 100
#define str "Данные некорректны\n"

int arr[N];

//0
int index_first_negative (int a[]){
    for (int i = 0; i < N; i++) {
        if (arr[i] < 0){
            return i;
            break;
        }
    }
    return -1;
}

//1
int index_last_negative (int a[]){
    for (int i=N-1; i>-1; i--){
        if (arr[i]<0){
            return i;
            break;
        }
    }
    return -1;
}

//2
int sum_between_negative (){
    int first=index_first_negative(arr);
    int last=index_last_negative(arr);
    int sum=0;
    if (first==-1){
        return -1;
    }
    else{
        for (int i=first; i<last; i++){
            sum+=abs(arr[i]);
        }
        return sum;
    }
}

//3
int sum_before_and_after_negative (){
    int first=index_first_negative(arr);
    int last=index_last_negative(arr);
    int sum=0;
    if (first==-1){
        return -1;
    }
    else{
        for (int i=0; i<first; i++){
            sum+=arr[i];
        }
        for (int i=last; i<N; i++){
            sum+=abs(arr[i]);
        }
        return sum;
    }
}

int main(){
    int znach;
    scanf("%d",&znach);
    //int arr[N];
    int i = 0;
    while (i < N) {
        scanf("%d", &arr[i]);
        i++;
        if (getchar() == '\n') {
            break;
        }
    }
    switch(znach){
        case 0:
            if (index_first_negative(arr)!=-1){
                printf("%d\n",index_first_negative(arr));
            }
            else{
                printf(str);
            }
            break;
        case 1:
            if (index_last_negative(arr)!=-1){
                printf("%d\n",index_last_negative(arr));
            }
            else{
                printf(str);
            }
            break;
        case 2:
            if (sum_between_negative()!=-1){
                printf("%d\n",sum_between_negative(arr));
            }
            else{
                printf(str);
            }
            break;
        case 3:
            if (sum_before_and_after_negative()!=-1){
                printf("%d\n",sum_before_and_after_negative(arr));
            }
            else{
                printf(str);
            }
            break;
        default:
            printf(str);
            break;
    }
}