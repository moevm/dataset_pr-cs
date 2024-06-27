#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"
#include "get_index.h"

int main() {
    int type, N;
    int arr[100];
    char c;
    scanf("%d%c", &type, &c);
    int i = 0;
    while (c != '\n') {
        scanf("%d%c", &arr[i], &c);
        i++;
    }
    N = i;
    int res = -1;
    switch (type) {
    case 0:
        res = index_first_negative(arr, N);
        break;
    case 1:
        res = index_last_negative(arr, N);
        break;
    case 2:
        res = sum_between_negative(arr, N);
        break;
    case 3:
        res = sum_before_and_after_negative(arr, N);
        break;
    default:
        printf("Данные некорректны\n");
        return 0;
    }
    if (res != -1) {
        printf("%d\n", res);
    }
    return 0;
}
