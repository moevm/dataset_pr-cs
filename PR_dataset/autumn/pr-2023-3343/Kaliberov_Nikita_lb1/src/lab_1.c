#include <stdio.h>
#include <stdlib.h>
const int n = 100;

int index_first_negative(int b[], int s){
    int i_fn;
    for(int i=0;i<s;i++){
        if(b[i]<0){
            i_fn = i;
            break;
        }
    }
    return i_fn;
}

int index_last_negative(int b[], int s){
    int i_ln;
    for(int i=s-1;i>=0;i--){
        if(b[i]<0){
            i_ln = i;
            break;
        }
    }
    return i_ln;
}

int sum_between_negative(int b[], int s){
    int sb_fn;
    int sb_ln;
    int sum_bn = 0;
    sb_fn = index_first_negative(b, s);
    sb_ln = index_last_negative(b, s);
    for(int i=sb_fn;i<sb_ln;i++){
        sum_bn += abs(b[i]);
    }
    return sum_bn;
}

int sum_before_and_after_negative(int b[], int s){
    int sum_ban = 0;
    int sba_fn;
    int sba_ln;
    sba_fn = index_first_negative(b, s);
    sba_ln = index_last_negative(b, s);
    for(int i=0;i<sba_fn;i++){
        sum_ban += abs(b[i]);
    }
    for(int i=sba_ln;i<s;i++){
        sum_ban += abs(b[i]);
    }
    return sum_ban;
}

int main(){
    int a;
    int b[100];
    int s = 0;
    char c;
    scanf("%d", &a);
    while(c != '\n'){
        scanf("%d%c", &b[s++],&c);
    }
    switch(a){
        case 0:
            printf("%d\n", index_first_negative(b, s));
            break;
        case 1:
            printf("%d\n", index_last_negative(b, s));
            break;
        case 2:
            printf("%d\n", sum_between_negative(b, s));
            break;
        case 3:
            printf("%d\n", sum_before_and_after_negative(b, s));
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }
}
