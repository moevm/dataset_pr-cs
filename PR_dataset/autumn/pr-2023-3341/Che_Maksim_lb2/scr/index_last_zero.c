int index_last_zero(int array[], int array_size){
        for(int i = array_size - 1; i >= 0; i--){
                if(array[i] == 0){
                        return i;
                }
        }
}

