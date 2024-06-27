#include <stdlib.h>
#include "abs_min.h"
int abs_min(int arr[], int n){
    int min_val = abs( arr[0] );
    int min_index = 0;
    int k;
    for ( k=1; k<n; ++k ){
        if (min_val > abs( arr[ k ])){
            min_val = abs( arr[ k ]); 
            min_index = k;
        }
    } 
    return min_index;
}