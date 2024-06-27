#include "input.h"
#include "output.h"

#define N 100

int main(){
    int arr[N];
    int func_id=0;
    int arr_elements_quantity=0;

    input(&func_id, arr, &arr_elements_quantity);
    output(&func_id, arr, &arr_elements_quantity);


	return 0;
}