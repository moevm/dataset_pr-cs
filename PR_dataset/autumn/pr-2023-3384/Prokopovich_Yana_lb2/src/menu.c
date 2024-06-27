# include <stdio.h>
# include "index_first_negative.h"
# include "index_last_negative.h"
# include "multi_between_negative.h"
# include "multi_before_and_after_negative.h"

int main() {
    int N = 20;
    int arr[N];
    int choice;
    scanf("%d", &choice);
    int i=0;
    char space =' ';
    while (i < N && space == ' ') {
        scanf("%d%c", &arr[i], &space);
        i++;
    }
    switch(choice){
        case 0:
        printf("%d\n", index_first_negative(arr, i));
        break;

        case 1: 
        printf("%d\n", index_last_negative(arr, i));
        break;

        case 2: 
        printf("%d\n", multi_between_negative(arr, i));
        break;

        case 3:
        printf("%d\n", multi_before_and_after_negative(arr, i));
        break;

        default: printf("Данные некорректны");
    }
    return 0;
}