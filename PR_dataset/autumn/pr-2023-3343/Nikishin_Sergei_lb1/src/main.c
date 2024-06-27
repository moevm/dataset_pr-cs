#include <stdio.h>
#include <stdlib.h>

#define max_dlina 100

int index_perviy_otriz(int arr[], int razmer){
    for(int i=0;i<razmer;i++){
        if(arr[i]<0){
            return i;
            break;
        }
    }
}

int index_posledniy_otriz(int arr[], int razmer){
    for(int i=razmer -1;i>=0;i--){
        if(arr[i]<0){
            return i;
            break;
        }
    }
}

int sum_mezdu(int arr[], int razmer){
    int summ = 0;
    for(int i = index_perviy_otriz(arr, razmer); i < index_posledniy_otriz(arr, razmer); i++){
        summ += abs(arr[i]);
    }
    return summ;
}

int sum_do_i_posle(int arr[], int razmer){
    int summ = 0;
    for(int i=0; i < index_perviy_otriz(arr, razmer); i++){
        summ += abs(arr[i]);
    }
    for(int i = index_posledniy_otriz(arr, razmer); i< razmer; i++){
        summ += abs(arr[i]);
    }
    return summ;
}

int main(){
    int key_value;
    scanf("%d", &key_value);

    int razmer = 0;
    int arr[max_dlina];
    while(getchar()!='\n'){
        scanf("%d", &arr[razmer]);
        razmer++;
    }

    switch(key_value){

        case 0:
            printf("%d\n", index_perviy_otriz(arr, razmer));
            break;

        case 1:
            printf("%d\n", index_posledniy_otriz(arr, razmer));
            break;

        case 2:
            printf("%d\n", sum_mezdu(arr, razmer));
            break;

        case 3:
            printf("%d\n", sum_do_i_posle(arr, razmer));
            break;

        default:
            printf("Данные некорректны");
    }
    return 0;
}

