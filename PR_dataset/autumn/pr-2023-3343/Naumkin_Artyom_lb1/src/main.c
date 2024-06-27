#include <stdio.h>
#include <stdlib.h>


int abs_max(int size_arr, int arr[]) {
        int mx = arr[0];

        for(int i = 1; i < size_arr; i++) {
                if(abs(arr[i]) > abs(mx))
                        mx = arr[i];
        }
        return mx;
}


int abs_min(int size_arr, int arr[]) {
        int mn = arr[0];

        for(int i = 1; i < size_arr; i++) {
                if(abs(arr[i]) < abs(mn))
                        mn = arr[i];
        }
        return mn;
}


int sum(int size_arr,int arr[]) {
        int sum = 0;

        for(int i = 0; i < size_arr; i++) {
                if(arr[i] == abs_max(size_arr, arr)) {
                        for(int j = i; j < size_arr; j++) {
                                sum += arr[j];
                        }
                        break;
                }
        }
        return sum;
}


int main() {
        int size = 1, arr[100];
        int num;

        scanf("%d", &num);
        scanf("%d", &arr[0]);
        while(getchar() != '\n') {
                scanf("%d", &arr[size]);
                size++;
        }
        switch(num) {
                case 0:
                        printf("%d", abs_max(size, arr));
                        break;
                case 1:
                        printf("%d", abs_min(size, arr));
                        break;
                case 2:
                        printf("%d", abs_max(size, arr) - abs_min(size, arr));
                        break;
                case 3:
                        printf("%d", sum(size, arr));
                        break;
                default:
                        printf("Данные некорректны");
                        break;

        }
        return 0;
}

