#include <stdio.h>

#include "print_answer.h"

#define N 100 




int main() {
    int chose, arr[N], i = 0;
    char space = ' ';
    scanf("%d", &chose);
    while (i < N && space == ' ') {
        scanf("%d%c", &arr[i], &space);
        i++;
    }
    print_answer(chose, arr, i);
    return 0;
}