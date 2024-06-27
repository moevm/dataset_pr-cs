#include <stdio.h>


int max_i(int s[], int len1){
    int mx = 0;
    for(int i = 0; i < len1; i++){
        if(s[i] > mx){
            mx = s[i];
        }
    }
    return mx;
}

int min_i(int s[], int len1){
    int mn = 10000;
    for(int i = 0; i < len1; i++){
        if(s[i] < mn){
            mn = s[i];
        }
    }
    return mn;
}

int sum_mn(int s[], int len1){
    int mn = 10000, sum = 0, suml = 0;
    for(int i = 0; i < len1; i++){
        if(s[i] < mn){
            mn = s[i];
            sum = sum + suml;
            suml = 0;
        }
        suml = suml + s[i];
    }
    return sum;
}

void main(){
    int n, len = 0, arr[100];
    char end;
    scanf("%d", &n);
    while(1){
        scanf("%d%c", &arr[len], &end);
        len = len + 1;
        if(end == '\n'){
            break;
        }
    }
    switch(n){
    case 0:
        printf("%d\n", max_i(arr, len));
        break;
    case 1:
        printf("%d\n", min_i(arr, len));
        break;
    case 2:
        printf("%d\n", max_i(arr, len) - min_i(arr, len));
        break;
    case 3:
        printf("%d\n", sum_mn(arr, len));
        break;
    default:
        printf("Данные некорректны\n");
        break;
    }
}
