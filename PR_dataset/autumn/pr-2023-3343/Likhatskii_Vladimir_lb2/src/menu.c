#include <stdio.h>
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"

void scan(int *c, int n[], int *s);
void process(int c, int n[], int s);

int main() {
    int cmd;
    int nums[100];
    int size;

    scan(&cmd, nums, &size);
    process(cmd, nums, size);

    return 0;
}

void scan(int *c, int n[], int *s) {
    scanf("%d", c);
    *s = 0;

    do {
        scanf("%d", &n[*s]);
        *s = *s + 1;
    } while (getchar() != '\n');
}

void process(int c, int n[], int s) {
    switch (c) {
    case 0:
        printf("%d", max(n, s));
        break;
    case 1:
        printf("%d", min(n, s));
        break;
    case 2:
        printf("%d", diff(n, s));
        break;
    case 3:
        printf("%d", sum(n, s));
        break;
    
    default:
        printf("Данные некорректны");
        break;
    }
}