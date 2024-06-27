#include <stdlib.h>
#include <stdio.h>
int index_first_zero(int mas[], int len){
        int g =0;
        for(; g < len; ++g){
                if (mas[g] == 0){
                        return g;
                }
        }
}

int index_last_zero(int mas[], int len){
        int g = len- 1;
        for(; g >= 0; --g){
                if (mas[g] == 0){
                        return g;
                }
        }
}

int sum_between(int mas[], int len){
        int cnt = 0;
        int ifz = index_first_zero(mas, len) + 1;
        int ilz = index_last_zero(mas, len);
        for(ifz; ifz < ilz; ++ifz){
                cnt += abs(mas[ifz]);
        }
        return cnt;
}

int sum_before_and_after(int mas[], int len){
        int cnt = 0, il = 0;
        int ifz = index_first_zero(mas, len);
        int ilz = index_last_zero(mas, len);
        for(; il < ifz; il++){
                cnt += abs(mas[il]);
        }
        for(--len;len> ilz; --len){
                cnt += abs(mas[len]);
        }
        return cnt;
}
int main(){
        int i = 0, n;
        char c;
        scanf("%d", &n);
        int m[100];
        do{
        scanf("%d", &m[i]);
        ++i;
        } while(( c =getchar())!= '\n');
        switch(n){
                case 0:
                        printf("%d\n", index_first_zero(m, i));
                        break;
                case 1:
                        printf("%d\n", index_last_zero(m, i));
                        break;
                case 2:
                        printf("%d\n", sum_between(m, i));
                        break;
                case 3:
                        printf("%d\n", sum_before_and_after(m, i));
                        break;
                default:
                        printf("Данные некорректны\n");
        }
        return 0;
}

