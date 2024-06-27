#include <stdio.h>
#include <stdlib.h>

int index_first_negative(int s[],int len) {
    for (int i=0; i<len; i++) {
        if (s[i]<0) {
            return i;
        }
    }
}

int index_last_negative(int s[],int len) {
    for (int i=len-1; i>=0; i--) {
        if (s[i]<0) {
            return i;
        }
    }
}

int multi_between_negative(int s[],int len) {
    int p=1;
    int a = index_first_negative(s,len);
    int b = index_last_negative(s,len);
    for (int i=a; i<b; i++) {
        p = p*s[i];
    }
    return p;
}

int multi_before_and_after_negative(int s[],int len) {
    int doo = 1;
    int pos = 1;
    int a = index_first_negative(s,len);
    int b = index_last_negative(s,len);
    for(int i=0; i<a; i++) {
        doo = doo*s[i];
    }
    for(int i=b; i<len; i++) {
        pos = pos*s[i];
    }
    return doo * pos;
}

int main() {
    int i;
    scanf("%d", &i);
    int s[20];
    int len = 0;
    
    while (len <= 20 && scanf("%d", &s[len])==1) {
        len++;
        if (getchar() == '\n') {
            break;
        }
    }
    
    switch(i) {
        case 0:
            printf("%d\n",index_first_negative(s,len));
            break;
        case 1:
            printf("%d\n",index_last_negative(s,len));
            break;
        case 2:
            printf("%d\n",multi_between_negative(s,len));
            break;
        case 3:
            printf("%d\n",multi_before_and_after_negative(s,len));
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }
}
