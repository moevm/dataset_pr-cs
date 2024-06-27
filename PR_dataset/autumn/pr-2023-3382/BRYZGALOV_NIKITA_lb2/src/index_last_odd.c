int index_last_odd(int array[], int length){
    int j;
    for(j = length-1; j > -1; j -= 1){
        if((array[j]%2) != 0){
            return j;
        }
    }
}