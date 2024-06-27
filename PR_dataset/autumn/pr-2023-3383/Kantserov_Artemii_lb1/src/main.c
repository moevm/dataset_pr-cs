#include <stdio.h>

int max(int a[], int b){
    int max, x;
    max = 0;
    for(x = 1; x < b; x++){
        if(max < a[x]){
            max = a[x];
        }
    }
    return max;
}
int min(int a[], int b){
    int min, x;
    min = 1e9;
    for(x = 1; x < b; x++){
        if(min > a[x]){
            min = a[x];
        }
    }
    return min;
}
int diff(int a[], int b){
    int min, x, max;
    min = 1e9;
    max = 0;
    for(x = 1; x < b; x++){
        if(max<a[x]){
            max = a[x];
        }
    }
    for(x = 1; x < b; x++){
        if(min > a[x]){
            min = a[x];
        }
    }
    return max-min;
}
int sum(int a[], int b){
    int min, x, i, sum;
    i = 0;
    min = 1e9;
    sum = 0;
    for(x = 1; x < b; x++){
        if(min > a[x]){
            i = x;
            min = a[x];
        }
    }
    for(x = 1; x < i; x++){
        sum += a[x];
    }
    return sum;
}

int main(void){
    int num[101];
    int size = 0;
    char input[10000];
    fgets(input, sizeof(input), stdin);
    int count = 0;
    while(sscanf(input + count, "%d", &num[size]) == 1 && size < 101){
        size++;
        while(input[count] != ' ' && input[count] != '\n'){
            count++;
        }
        while(input[count] == ' ' || input[count] == '\n'){
            count++;
        }
    }
    int put = 0;
    switch (num[0]) {
        case 0:
            put = max(num, size);
            printf("%d", put);
            break;
        case 1:
            put = min(num, size);
            printf("%d", put);
            break;
        case 2:
            put = diff(num, size);
            printf("%d", put);
            break;
        case 3:
            put = sum(num, size);
            printf("%d", put);
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }
    return 0;
}
