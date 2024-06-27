#include <stdlib.h>
int abs_max(int * array, int input_length){
        int abs_max = array[0];
        for(int i=0; i!=input_length; i++){
                if (abs(abs_max) < abs(array[i])){
                        abs_max = array[i];
                }
        }
        return abs_max;
}
