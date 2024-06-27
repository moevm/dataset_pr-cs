#include <stdio.h>
#include <stdlib.h>

int abs_max_i(int* m, int n) {
    int maximum = 0;
    for (int i = 1; i < n; i++) {
        if (abs(m[maximum]) < abs(m[i])) {
            maximum = i;
        }
    }
    return maximum;
}
int abs_min_i(int* m, int n) {
    int minimum = 0;
    for (int i = 1; i < n; i++) {
        if (abs(m[minimum]) > abs(m[i])) {
            minimum = i;
        }
    }
    return minimum;
}
int abs_max(int* m, int n) {
    int a = abs_max_i(m, n);
    return m[a];
}
int abs_min(int* m, int n) {
    int a = abs_min_i(m, n);
    return m[a];
}
int diff(int* m, int n) {
    return abs_max(m, n) - abs_min(m, n);
}
int sum(int* m, int n) {
    int s = 0;
    for (int i = abs_max_i(m, n); i < n; i++) {
        s += m[i];
    }
    return s;
}
int main() {
    int size, mode, numbers[100];
    size = 0;
    char perev_str = ' ';
    scanf("%d", &mode);

    for (int i = 0; perev_str != '\n'; i++) {
        scanf("%d%c", &numbers[i], &perev_str);
        size = i + 1;
    }
    switch (mode) {
    case 0:
        printf("%d", abs_max(numbers, size));
        break;
    case 1:
        printf("%d", abs_min(numbers, size));
        break;
    case 2:
        printf("%d", diff(numbers, size));
        break;
    case 3:
        printf("%d", sum(numbers, size));
        break;
    default:
        printf("Данные некорректны");
        break;
    }
}
