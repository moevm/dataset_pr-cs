#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"
#include "index_last_zero.h"





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

