#include "abs_max.h"
#include <stdlib.h>
int abs_max(int arr[], int n){
    int max_val = abs( arr[0] );
    int max_index = 0;
    int k;
    for ( k=1; k<n; ++k ){
        if (max_val < abs(arr[ k ])){
            max_val = abs(arr[ k ]);
            max_index = k; 
        }
    } 
    return max_index;
}