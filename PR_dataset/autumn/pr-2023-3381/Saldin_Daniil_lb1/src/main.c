#include <stdio.h>
#include <stdlib.h>
int index_first_zero(int len_arr_i, int arr_i[]){
    for(int i = 0; i < len_arr_i; i++){
        if(arr_i[i] == 0){
            return i;
        }
    }
}
int index_last_zero(int len_arr_i, int arr_i[]){
    for(int i = (len_arr_i- 1); i >= 0; i--){
        if(arr_i[i] == 0){
            return i;
        }
    }
}
int sum_between(int len_arr_i, int arr_i[]){
    int sum_b = 0;
    int fst_zero = index_first_zero(len_arr_i, arr_i);
    int ls_zero = index_last_zero(len_arr_i, arr_i);
    for(int i = (fst_zero + 1); i < ls_zero; i++ ) {
        sum_b += llabs(arr_i[i]);
    }
    return sum_b;
}
int sum_before_and_after(int len_arr_i, int arr_i[]){
    int sum_b_af= 0;
    int fst_zero = index_first_zero(len_arr_i, arr_i);
    int ls_zero = index_last_zero(len_arr_i, arr_i);
    for(int i = 0; i < fst_zero; i++ ) {
        sum_b_af += llabs(arr_i[i]);
    }
    for(int i = (ls_zero + 1); i < len_arr_i; i++ ) {
        sum_b_af += llabs(arr_i[i]);
    }
    return sum_b_af;
}
int main() {
    int fun_sel;
    int arr_i[100];
    int len_arr_i = 0;
    scanf("%d", &fun_sel);
    int pr = getchar();
    while (pr != '\n') {
        if (pr == ' ') {
            scanf("%d", &arr_i[len_arr_i]);
            len_arr_i++;
        }
        pr = getchar();
    }
    switch(fun_sel){
        case 0:
            printf("%d\n", index_first_zero(len_arr_i, arr_i));
            break;
        case 1:
            printf("%d\n", index_last_zero(len_arr_i, arr_i));
            break;
        case 2:
            printf("%d\n", sum_between(len_arr_i, arr_i));
            break;
        case 3:
            printf("%d\n", sum_before_and_after(len_arr_i, arr_i));
            break;
        default:
            printf("Данные некорректны\n");
    }
    return 0;
}