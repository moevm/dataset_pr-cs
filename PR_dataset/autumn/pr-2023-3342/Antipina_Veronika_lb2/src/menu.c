#include <stdio.h>
#define N 20
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"


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
