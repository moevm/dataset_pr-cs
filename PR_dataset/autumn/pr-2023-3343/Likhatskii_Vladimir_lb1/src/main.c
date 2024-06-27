#include <stdio.h>

void scan(int *c, int n[], int *s);
void process(int c, int n[], int s);
int max(int n[], int s);
int min(int n[], int s);
int diff(int n[], int s);
int sum(int n[], int s);

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

int max(int n[], int s) {
    int m = n[0]; 

    int i;
    for(i = 0; i < s; i++) {
        if(n[i] > m) m = n[i];
    }

    return m;
}

int min(int n[], int s) {
    int m = n[0]; 

    int i = 0;
    for(i = 0; i < s; i++) {
        if(n[i] < m) m = n[i];
    }

    return m;
}

int diff(int n[], int s) {
    return max(n, s) - min(n, s);
}

int sum(int n[], int s) {
    int res = 0; 
    int m = min(n, s); 

    int i = 0; 
    while(n[i] != m) {
        res += n[i];
        i++;
    }

    return res;
}