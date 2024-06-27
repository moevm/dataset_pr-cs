#include "index_last_odd.h"
int index_last_odd(int array[],int number_of_numbers){
    int last_odd;
    for(int i=0;i<number_of_numbers;i++){
        if(array[i]%2!=0) last_odd=i;
    }
    return last_odd;
}
