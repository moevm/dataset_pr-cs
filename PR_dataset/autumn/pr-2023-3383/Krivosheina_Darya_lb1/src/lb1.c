#include <stdio.h>

int max(int mass0[], int len0);

int min(int mass1[], int len1);

int diff(int mass2[], int len2);

int sum(int mass3[], int len3);

int main(){
    int n;
    scanf("%d", &n);
    int len = 0;
    int mass[100] = {0};
    for (int i = 0; i < 100; i++){
        scanf("%d", &mass[i]);
        len++;
        if (getchar() == '\n'){
            break;
        }
    }
    if (n == 0){
        printf("%d\n", max(mass, len));
    } else if(n == 1){
        printf("%d\n", min(mass, len));
    } else if(n == 2){
         printf("%d\n", diff(mass, len));
    } else if(n == 3){
        printf("%d\n", sum(mass, len));
    } else{
        printf("Данные некорректны");
    }
    return 0;
}

int max(int mass0[], int len0){
    int maxim = 0;
    for (int i = 0; i < len0; i++){
        if (mass0[i] > maxim){
            maxim = mass0[i];
        } 
    }
    return maxim;
}

int min(int mass1[], int len1){
    int minim = 1000;
    for (int i = 0; i < len1; i++){
        if (mass1[i] < minim){
            minim = mass1[i];
        }
    }
    return minim;
}

int diff(int mass2[], int len2){
    int dif, minim = 1000, maxim = 0;
    for(int i = 0; i < len2; i++){
        if (mass2[i] < minim){
            minim = mass2[i];
        } 
    }
    for (int i = 0; i < len2; i++){
        if (mass2[i] > maxim){
            maxim = mass2[i];
        }
    }
    dif = maxim - minim;
    return dif;
}

int sum(int mass3[], int len3){
    int minim = 1000, summ = 0;
    for (int i = 0; i < len3; i++){
        if (mass3[i] < minim){
            minim = mass3[i];
        }
    }
    for(int i = 0; i < len3; i++){
        if (mass3[i] == minim){
            break;
        } else {
            summ += mass3[i];
        }
    }
    return summ;
}
