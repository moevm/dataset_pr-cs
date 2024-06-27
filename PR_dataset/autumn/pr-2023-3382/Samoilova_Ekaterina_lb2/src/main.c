#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"

      int main()
    { int arr[20];
    int N = 0;
    int numb = 0;
    scanf ("%d", &numb);
    char c;
    while (c!='\n'){
    scanf("%d%c", &arr[N], &c);
    N++;
}
        
    switch(numb){
    case 0:
    printf("%d\n",index_first_negative(arr, N));
    break;
    case 1:
    printf("%d\n",index_last_negative(arr,  N));
    break;
    case 2:
    printf("%d\n",multi_between_negative(arr,  N));
    break;
    case 3:
    printf("%d\n",multi_before_and_after_negative(arr,  N));
    break;
    default:
    printf("Данные некорректны");
    };

    return 0;
}

