#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"


int main()
{
    int n = 0;
    int menu;
    scanf("%d", &menu);
    int arr[20];
    while(n < 20){
        scanf("%d", &arr[n]);
        n++;
        if (getchar() == '\n'){
            break;
        }
    }
    switch (menu) {
        case 0:
            printf("%d\n", index_first_negative(arr,n));
            break;
        case 1:
            printf("%d\n", index_last_negative(arr,n));
            break;
        case 2:
            printf("%d\n", multi_between_negative(arr,n));
            break;
        case 3:
            printf("%d\n", multi_before_and_after_negative(arr,n));
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }
    return 0;
}
