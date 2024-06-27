#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
/**
 * Get:
 *      (int) arr_len
 *      (int) arr[]
 * Retunrn:
 *      (int) max abs in arr[]
 */

int abs_max(int arr_len, int arr[]){
        int mx = 0;

        for (int i = 0; i < arr_len; i++) {
                if (abs(arr[i]) > abs(mx)){
                        mx = arr[i];
                }
        }
        return mx;
}
/**
 * Get:
 *      (int) arr_len
 *      (int) arr[]
 * Return:
 *      (int) min abs in arr[]
 */
int abs_min(int arr_len, int arr[]){
        int mn = INT_MAX;
        for (int i = 0; i < arr_len; i++){
                if (abs(arr[i]) < abs(mn)){
                        mn = arr[i];
                }
        }
        return mn;
}
/**
 * Get:
 *      (int) arr_len
 *      (int) arr[]
 *  Return:
 *      (int) diff between abs_max() & abs_min()
 */
int diff(int arr_len, int arr[]){
        return abs_max(arr_len, arr) - abs_min(arr_len, arr);
}
/**
 * Get:
 *      (int) arr_len
 *      (int) arr[]
 * Return:
 *      (int) summ all elements after max
 */
int sum(int arr_len, int arr[]){
        int mx = abs_max(arr_len, arr);
        int s = 0;
        for(int i = 0; i < arr_len; i++){
                if (s) s += arr[i];
                else if (abs(arr[i]) == abs(mx)) s += mx;
        }
        return s;
}

void main(){
        int n;
        int arr[100];

        scanf("%d", &n);
        int act_size = 0;
        while (getchar() != '\n') {
                scanf("%d", &arr[act_size]);
                act_size++;
        }
        switch (n){
                case 0:
                        printf("%d", abs_max(act_size, arr));
                        break;
                case 1:
                        printf("%d", abs_min(act_size, arr));
                        break;
                case 2:
                        printf("%d", diff(act_size, arr));
                        break;
                case 3:
                        printf("%d", sum(act_size, arr));
                        break;
                default:
                        printf("Данные некорректны");
                        break;
        }
}
