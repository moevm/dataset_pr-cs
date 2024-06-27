#include <stdlib.h>
int abs_min(int arr[], int size) {
    int min = 1001;
    for (int i = 0; i < size; i++) {
        if (abs(arr[i]) < abs(min)) {
            min = arr[i];
        }
     }
return min;
}
