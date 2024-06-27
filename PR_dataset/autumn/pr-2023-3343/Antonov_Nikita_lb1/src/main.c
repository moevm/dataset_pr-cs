#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int index_first_negative(int i, int sp[]){
    for(i = 0; i < 20; i++){
        if(sp[i] < 0){
            return i;
            break;
        }
    }
    return 0;
}

int index_last_negative(int i, int sp[]){
    for(i = 19; i > -1; i--){
        if(sp[i] < 0){
            return i;
            break;
        }
    }
    return 0;
}

int multi_between_negative(int i,int sp[], int su){
    int pr1 = 0, pr2 = 0;
    for(i = 0; i < 20; i++){
        if(sp[i] < 0){
            pr1 += 1;
        }
    }
    for(i = 0; i < 20; i++){
        if(sp[i] < 0){
            pr2 += 1;
        }
        if((pr2 >= 1) && (pr2 < pr1)){
            su = su * sp[i];
        }
    }
    return su;
}

int multi_before_and_after_negative(int i,int sp[], int su){
    int pr3 = 0, pr4 = 0;
    for(i = 0; i < 20; i++){
        if(sp[i] < 0){
            pr3 += 1;
        }
    }
    i = 0;
    for(i = 0; i < 20; i++){
        if(sp[i] < 0){
            pr4 += 1;
        }
        if((pr4 < 1) || (pr4 >= pr3)){
            su = su * sp[i];
        }
    }
    return su;
}

int main(){
    setlocale(LC_ALL, "Rus");
    int a , sp[20], i = 0, r = 0, su = 1;
    for(i = 0; i < 20; i++){
        sp[i] = 1;
    }
    i = 0;
    scanf("%d", &a);
 do {
        scanf("%d", &sp[i]);
        i++;
    }
    while (getchar() != '\n');
    switch (a)
    {
    case 0:
        r = index_first_negative(i, sp);
        printf("%d", r);
        break;
    case 1:
        r = index_last_negative(i, sp);
        printf("%d", r);
        break;
    case 2:
        r = multi_between_negative(i, sp, su);
        printf("%d", r);
        break;
    case 3:
        r = multi_before_and_after_negative(i, sp, su);
        printf("%d", r);
        break;
    default:
        printf("Данные некорректны");
        break;
    }
}