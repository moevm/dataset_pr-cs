#include "diff.h"
#include "abs_min.h"
#include "abs_max.h"

int diff(int arr[], int n){
    int min_index = abs_min( arr, n );
    int max_index = abs_max( arr, n );
    return arr[ max_index ] - arr[ min_index ];
}