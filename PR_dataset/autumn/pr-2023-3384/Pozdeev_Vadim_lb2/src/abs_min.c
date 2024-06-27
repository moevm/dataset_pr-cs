#include <stdlib.h>
int abs_min(int * array, int input_length){
        int abs_min = array[0];
        for(int i=0; i!=input_length; i++){
                if(abs(abs_min) > abs(array[i])){
                        abs_min = array[i];
                }
        }
        return abs_min;
}
