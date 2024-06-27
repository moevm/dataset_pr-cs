#include <stdlib.h>
int sum(int * array, int input_length){
        int abs_max = array[0];
        int sum = array[0];
        for(int i = 1; i!=input_length; i++){
            if(abs(abs_max) < abs(array[i])){
                sum = array[i];
                abs_max = array[i];
            }
            else{
                sum += array[i];
            }
        }
    return sum;
}
