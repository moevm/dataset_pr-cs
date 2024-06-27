#include "len.h"
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"

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