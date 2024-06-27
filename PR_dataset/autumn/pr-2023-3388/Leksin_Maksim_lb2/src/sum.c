#include "sum.h"

int sum(int arr[], int size, int id_max) {
        int summ = 0;
        for (int i = id_max; i < size; i++) {
                summ = summ + arr[i];
        }
        return summ;
}
