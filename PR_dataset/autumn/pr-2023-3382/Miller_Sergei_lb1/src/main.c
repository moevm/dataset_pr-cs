#include <stdio.h>
#include <stdlib.h>


int index_first_zero(int m[], int lenm) {
        for (int i = 0; i < lenm; i++){
                if (m[i]== 0)
                        return i;
        }
        return -1;
}


int index_last_zero(int m[], int lenm){
        for (int i = lenm - 1; i != 0; i--){
                if (m[i] == 0){
                        return i;
                }
        }
        return -1;
}


int sum_between(int m[], int fz, int lz) {
        int sum_btw = 0;
        for (int i = fz + 1; i < lz;  i++){
                sum_btw += abs(m[i]);
        }
        return sum_btw;
}


int sum_before_and_after(int m[], int lenm,  int fz, int lz) {
        int sum_bf_af = 0;
        for (int i = 0; i < fz; i++){
                sum_bf_af += abs(m[i]);
        }
        for (int i = lz; i < lenm; ++i){
                sum_bf_af += abs(m[i]);
        }
        return sum_bf_af;
}


int  main() {
        char check;
        int a, m[101];
        int lenm = 0;
        scanf("%d%c", &a, &check);
        for (int i = 0; i < 101; i++){

                if (check == '\n'){
                        break;
                }
                else{
                        scanf("%d%c", &m[i], &check);
                        ++lenm;
                }
        }
        int f_z  = index_first_zero(m, lenm);
        int l_z = index_last_zero(m, lenm);
        switch (a) {
            case 0:
                printf("%d\n", f_z);
                break;
            case 1:
                printf("%d\n", l_z);
                break;
            case 2:
                printf("%d\n", sum_between(m, f_z, l_z));
                break;
            case 3:
                printf("%d\n", sum_before_and_after(m, lenm, f_z, l_z));
                break;
            default:
                printf("Данные некорректны\n");
        }


        return 0;
}
