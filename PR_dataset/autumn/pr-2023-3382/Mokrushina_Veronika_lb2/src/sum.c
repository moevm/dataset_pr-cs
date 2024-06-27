#include "sum.h"
#include "abs_max.h"
int sum(int arr[], int n){
    int max_index = abs_max( arr, n );
    int j, suma = 0;
    for (j=max_index; j<n; ++j ){
        suma += arr[ j ];
    }
    return suma;
}
