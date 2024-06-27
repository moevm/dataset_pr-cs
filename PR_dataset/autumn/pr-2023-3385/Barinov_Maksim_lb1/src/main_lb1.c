#include <stdio.h>
int max(int a[], int len) {
    int m = a[0];
    for (int i =0 ; i < len; i++) {
        if (a[i] > m) m = a[i];
    }
    return m;
}
int min(int a[], int len) {
    int m = a[0];
    for (int i =0 ; i < len; i++) {
        if (a[i] < m) m = a[i];
    }
    return m;
}
int diff(int a[], int len) {
    return max(a, len) - min(a, len);
}
int sum(int a[], int len) {
    int m = min(a, len), sum = 0;
    for (int i = 0; i < len; i++) {
        if (a[i] == m) {
            break;
        } else {
            sum += a[i];
        }
    }
    return sum;
}
int main() {
    int a[100];
    int len = 0, ell, com;
    scanf("%d", &com);
    char c;
    while(c != '\n') {
        scanf("%d%c", &ell, &c);
        a[len++] = ell;
    }
    switch (com) {
        case 0:
            printf("%d\n", max(a, len));
            break;
        case 1:
            printf("%d\n", min(a, len));
            break;
        case 2:
            printf("%d\n", diff(a, len));
            break;
        case 3:
            printf("%d\n", sum(a, len));
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }
}
