int index_first_zero(int array[], int array_size){
        for(int i = 0; i < array_size; i++){
                if(array[i] == 0){
                    return i;
                }
        }
}
