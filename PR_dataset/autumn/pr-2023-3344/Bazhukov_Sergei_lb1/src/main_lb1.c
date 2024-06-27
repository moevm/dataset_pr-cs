#include <stdio.h>


int len(int *array){
    int arr_len=0;
    do{
       scanf("%d",&array[arr_len]);
       arr_len++;
    } while (getchar()!='\n');
    return arr_len;
}

int max(int *array,int arr_len){
    int maxon=array[0];
    for (int i=0; i<arr_len; i++){
        if(array[i]>maxon){
            maxon=array[i];
        }
    }
    return maxon;
}

int min(int *array,int arr_len){
    int minon=array[0];
    for (int i=0; i<arr_len; i++){
        if(array[i]<minon){
            minon=array[i];
        }
    }
    return minon;
}

int diff(int *array,int arr_len){
    int difference = max(array,arr_len)-min(array,arr_len);
    return difference;
}

int sum(int *array,int arr_len){
    int sum=0;
    int minon = min(array,arr_len);
    for(int i=0;array[i]>minon;i++){
        sum=sum+array[i];
    }
    return sum;
}



int main(){
    int choice = 5;
    scanf("%d",&choice);
    int array[100]={0};
    int arr_len = len(array);

    switch(choice){
        case 0:
            printf("%d\n", max(array,arr_len));
            break;
        case 1:
            printf("%d\n", min(array,arr_len));
            break;
        case 2:
            printf("%d\n", diff(array,arr_len));
            break;
        case 3:
            printf("%d\n", sum(array,arr_len));
            break;
        default:
            printf("Данные некорректны\n");

    }
    return 0;
}