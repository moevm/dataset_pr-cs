#include <stdio.h>
#define N 20

int index_first_negative(int arr[],int size){
        int index_first_neg;

        index_first_neg = -1;
        for(int i=0;i<size;i++){
                if (arr[i]<0){
                        index_first_neg = i;
                        break;
                }
        }
        if (index_first_neg != -1){
                return index_first_neg;}
        else{puts("Данные некорректны");}
}
int index_last_negative(int arr[], int size){
        int indexlastneg;

        for(int i=0;i<size;i++){
                if (arr[i]<0){
                        indexlastneg = i;
                }
        }
        return indexlastneg;
}
void multi_between_negative(int arr[],int size){
        int multi = 1;
        int index_first_neg, index_last_neg, i;

        index_first_neg = index_first_negative(arr,size);

        index_last_neg = index_last_negative(arr,size);

        for(i = index_first_neg;i<index_last_neg;i++){
                multi=multi*arr[i];
        }
        printf("%d\n", multi);
}
void  multi_before_and_after_negative(int arr[],int size){
        int multi = 1;
        int index_first_neg, index_last_neg;

        index_first_neg = index_first_negative(arr,size);
        index_last_neg = index_last_negative(arr,size);

        for(int i=0;i<index_first_neg;i++){
                multi*=arr[i];
        }

        for(int i=index_last_neg;i<size;i++){
                multi*=arr[i];
        }

        printf("%d\n", multi);
}
void input(int arr[], int* size, int* for_cases) {
        int i = 0;
        char space;

        scanf("%d%c", for_cases, &space);

        while (i < N && space == ' ') {
                scanf("%d%c", &arr[i], &space);
                (*size)++;
                i++;
        }
}
void menu(int for_cases,int arr[],int size){
    switch(for_cases){
            case 0:
                    printf("%d\n", index_first_negative(arr,size));
                    break;
            case 1:
                    printf("%d\n", index_last_negative(arr,size));
                    break;
            case 2:
                    multi_between_negative(arr,size);
                    break;
            case 3:
                    multi_before_and_after_negative(arr,size);
                    break;
            default:
                    puts("Данные некорректны");
                    break;
    }
}
int main(){
        int arr[N];
        int size = 0;
        int for_cases;

        input(arr, &size, &for_cases);
        menu(for_cases,arr,size);
        return 0;
}
