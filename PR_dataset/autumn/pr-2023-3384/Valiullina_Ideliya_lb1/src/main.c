#include <stdio.h>
#include <stdlib.h>
#define N 100

int abs_max(int a[], int n){
    int a_max_ans, a_abs_max = 0;
    for(int i = 0; i < n; i++){
        if(abs(a[i]) > a_abs_max){
            a_abs_max = abs(a[i]);
            a_max_ans = a[i];
        }
    }
    return a_max_ans;
}

int abs_min(int a[], int n){
    int a_min_ans = a[0], a_abs_min = abs(a[0]);
    for(int i = 0; i < n; i++){
        if(abs(a[i]) < a_abs_min){
            a_abs_min = abs(a[i]);
            a_min_ans = a[i];
        }
    }
    return a_min_ans;
}

int diff(int a[], int n){
    return abs_max(a,n) - abs_min(a,n);
}

int sum(int a[], int n){
    int flag = 0, sum = 0;

    for(int i = 0; i < n; i++){
        if(a[i] == abs_max(a,n)){
            flag = 1;
        }
        if(flag != 0){
            sum += a[i];
        }
    }
    return sum;
}

int main()
{
    int f, n = 0;
    scanf("%d", &f);

    int a[N];
    char x = getchar();
    for(int i = 0; i < N; i++){
        if(x == '\n')
            break;
        else{
            scanf("%d", &a[i]);
            x = getchar();
            n++;
        }
    }

    switch(f){
        case 0:
            printf("%d\n", abs_max(a, n));
            break;
        case 1:
            printf("%d\n", abs_min(a, n));
            break;
        case 2:
            printf("%d\n", diff(a, n));
            break;
        case 3:
            printf("%d\n", sum(a, n));
            break;
        default:
            printf("Данные некорректны\n");
    }
    return 0;
}